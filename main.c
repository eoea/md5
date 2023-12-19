#include <openssl/evp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void calculate_md5(const char *pathname) {
  EVP_MD_CTX *mdctx;
  unsigned int md_len;
  unsigned char md_value[EVP_MAX_MD_SIZE];

  mdctx = EVP_MD_CTX_new();

  (void)EVP_DigestInit_ex(mdctx, EVP_md5(), NULL);
  (void)EVP_DigestUpdate(mdctx, pathname, strlen(pathname));
  (void)EVP_DigestFinal_ex(mdctx, md_value, &md_len);

  EVP_MD_CTX_free(mdctx);

  (void)printf("Digest is: ");
  for (size_t i = 0; i < md_len; i++)
    (void)printf("%02x", md_value[i]);
  (void)printf("\n");
}

char *calculate_md5_from_file_malloc(char *filepath) {
  FILE *fp;
  int buf;
  char *hex_string;
  unsigned int md_len;
  unsigned char md_value[EVP_MAX_MD_SIZE];
  unsigned char content[4096];
  EVP_MD_CTX *mdctx;

  fp = fopen(filepath, "rb");
  if (fp == NULL) {
    (void)fprintf(stderr, "ERROR: Could not open path.\n");
    return NULL;
  }
  mdctx = EVP_MD_CTX_new();
  (void)EVP_DigestInit_ex(mdctx, EVP_md5(), NULL);
  while ((buf = fread(content, 1, 4096, fp)) != 0) {
    (void)EVP_DigestUpdate(mdctx, content, buf);
  }
  (void)EVP_DigestFinal_ex(mdctx, md_value, &md_len);

  EVP_MD_CTX_free(mdctx);
  fclose(fp);

  hex_string = (char *)malloc(EVP_MAX_MD_SIZE);
  if (hex_string == NULL) {
    (void)fprintf(stderr, "ERROR: Could not malloc\n");
    return NULL;
  }

  for (size_t i = 0; i < md_len; i++) {
    (void)sprintf(&hex_string[2 * i], "%02x", md_value[i]);
  }

  return hex_string;
}

int main(void) {
  calculate_md5("Hello world");

  char *hex_string;
  hex_string = calculate_md5_from_file_malloc("main.c");
  (void)printf("Digest is: %s\n", hex_string);
  free(hex_string);

  return EXIT_SUCCESS;
}
