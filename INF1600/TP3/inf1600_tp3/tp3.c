/*
Auteur: Philippe Proulx <eepp.ca>
Mise à jour par:
Adrien Vergé <adrien.verge@polymtl.ca>
Karim Keddam <karim.keddam@polymtl.ca>
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

// taille du tampon de sortie
#define OUTPUT_BUF_SIZE	(1024 * 1024 * 16)

// tampon de sortie
uint8_t g_output_buf [OUTPUT_BUF_SIZE];

// fonction filtre en assembleur
extern size_t filter(const uint8_t* in_buf, uint32_t w, uint32_t h);

static void error(const char* msg, const int exit_code) {
	fprintf(stderr, "erreur : %s\n", msg);
	exit(exit_code);
}

static uint8_t* load_file(const char* filename, uint32_t* w, uint32_t* h) {
	uint8_t header_buf [0x36];
	uint8_t* buf;
	uint8_t px [4] = {0};
	uint32_t k;
	FILE* fh = fopen(filename, "rb");
	int32_t x, y;
	off_t offset;

	if (fh == NULL) {
		error("impossible d'ouvrir le fichier en lecture", 1);
	}
	fread(header_buf, 1, 0x36, fh);
	k = *((uint32_t*) (header_buf + 0x1c));
	if (k != 24) {
		error("fichier Bitmap invalide", 3);
	}
	k = *((uint32_t*) (header_buf + 0xe));
	if (k != 40) {
		error("fichier Bitmap invalide : mauvais entête", 3);
	}
	*w = *((uint32_t*) (header_buf + 0x12));
	*h = *((uint32_t*) (header_buf + 0x16));
	if ((*w & 3) != 0) {
		error("la largeur de l'image Bitmap n'est pas un multiple de 4", 3);
	}
	buf = (uint8_t*) malloc(3 * *w * *h);
	for (y = *h - 1; y >= 0; --y) {
		for (x = 0; x < *w; ++x) {
			offset = 3 * (y * *w + x);
			if (fread(px, 1, 3, fh) != 3) {
				free(buf);
				error("impossible de lire le fichier Bitmap au complet", 3);
			}
			buf[offset] = px[2];
			buf[offset + 1] = px[1];
			buf[offset + 2] = px[0];
		}
	}
	fclose(fh);

	return buf;
}

static void output_file(const uint8_t* buf, size_t sz, const char* filename) {
	FILE* fh = fopen(filename, "wb");
	if (fh == NULL) {
		error("impossible d'ouvrir le fichier en écriture", 1);
	}
	fwrite(buf, 1, sz, fh);
	fclose(fh);
}

/* Cette fonction écrit les entêtes BMP et DIB dans le tampon de sortie.
    Cette fonction est là uniquement pour vous guider dans l'écriture du code assembleur
    qui se charge de l'entête BMP et DIB.
    VOUS NE DEVEZ PAS faire appel à cette fonction.
*/
static void writeHeader(uint32_t w, uint32_t h)
{
  *g_output_buf = 'B';
	*(g_output_buf + 0x01) = 'M';
	*((uint16_t*)(g_output_buf + 0x06)) = 0;
	*((uint16_t*)(g_output_buf + 0x08)) = 0;
	*((uint32_t*)(g_output_buf + 0x0a)) = 54;
	*((uint32_t*)(g_output_buf + 0x0e)) = 40;
	*((uint32_t*)(g_output_buf + 0x12)) = w;
	*((uint32_t*)(g_output_buf + 0x16)) = h;
	*((uint16_t*)(g_output_buf + 0x1a)) = 1;
	*((uint16_t*)(g_output_buf + 0x1c)) = 24;
	*((uint32_t*)(g_output_buf + 0x1e)) = 0;
	*((uint32_t*)(g_output_buf + 0x26)) = 11811;
	*((uint32_t*)(g_output_buf + 0x2a)) = 11811;
	*((uint32_t*)(g_output_buf + 0x2e)) = 0;
	*((uint32_t*)(g_output_buf + 0x32)) = 0;
	uint32_t nbOctets = w * h * 3;
	*((uint32_t*)(g_output_buf + 0x22)) = nbOctets;
	*((uint32_t*)(g_output_buf + 0x02)) = (nbOctets + 54);
}

int main(const int argc, char* argv []) {
	uint8_t* input_bitmap_buf;
	size_t output_bitmap_sz;
	uint32_t w, h;

	// vérifier les arguments de ligne de commande
	if (argc != 3) {
		fprintf(stderr, "usage : %s <entrée BMP> <sortie BMP>\n",
			argv[0]);
		exit(2);
	}

	char* in = argv[1];
    char* out = argv[2];

	// charger le fichier Bitmap en lecture
	printf("chargement de l'image Bitmap \"%s\" en entrée...\n", in);
	input_bitmap_buf = load_file(in, &w, &h);
	printf("image Bitmap \"%s\" chargée (%u x %u)\n", argv[1], w, h);
	printf("w:%d h:%d\n", w,h);
	// filtrer et remplir le tampon d'écriture
	puts("filtrage...");
	output_bitmap_sz = filter(input_bitmap_buf, w, h);
	printf("%u octets retournés\n", output_bitmap_sz);
	free(input_bitmap_buf);

	// créer le fichier en sortie
	printf("écriture de l'image Bitmap \"%s\" en sortie...\n", out);
	output_file(g_output_buf, output_bitmap_sz, out);

	puts("terminé!");

	return EXIT_SUCCESS;
}
