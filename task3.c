#include "task3.h"

#define NR_OF_BLOCKS 4

void XOR(unsigned char *block, size_t block_size, const unsigned char *iv, size_t iv_len) {
    for (size_t i = 0; i < block_size; i++) {
        block[i] = block[i] ^ iv[i % iv_len];
    }
}

void P_BOX(unsigned char *block, size_t block_size) {
    // Create a copy of the block
    unsigned char *result = malloc(block_size * sizeof(*result));

    // Apply the P-BOX
    size_t pos = 0;
    for (size_t i = 0; i < block_size; i++) {
        pos = (i * (block_size - 1) + 2) % block_size;
        result[pos] = block[i];
    }

    memcpy(block, result, block_size);

    // Free memory
    free(result);
}

void cripteaza_studenti(secretariat *secretariat, void *key, size_t key_len,
                        void *iv, size_t iv_len, char *cale_output) {
    // Find the number of studenti
    int nr_stud = secretariat->nr_studenti;

    // Find size of studenti array in bytes
    size_t blocks_length = sizeof(student) * nr_stud;

    // Find the number of padding bytes
    uint8_t padding_bytes = 0;
    if (blocks_length % NR_OF_BLOCKS != 0) {
        padding_bytes = NR_OF_BLOCKS - (blocks_length % NR_OF_BLOCKS);
    }

    // Create a copy of the studenti array for accessing every byte
    unsigned char *plainBytes = calloc((blocks_length + padding_bytes), 1);
    memmove(plainBytes, secretariat->studenti, blocks_length);

    blocks_length += padding_bytes;

    // Split into 4 blocks
    size_t block_size = blocks_length / NR_OF_BLOCKS;
    unsigned char **blocks = malloc(NR_OF_BLOCKS * sizeof(*blocks));
    for (int i = 0; i < NR_OF_BLOCKS; i++) {
        blocks[i] = malloc(block_size * sizeof(**blocks));
    }
    for (int i = 0; i < NR_OF_BLOCKS; i++) {
        memmove(blocks[i], plainBytes + i * block_size, block_size);
    }

    // Free memory
    free(plainBytes);

    // Encrypt first block with IV
    XOR(blocks[0], block_size, iv, iv_len);

    // Encrypt first block with key
    XOR(blocks[0], block_size, key, key_len);

    // P-BOX
    P_BOX(blocks[0], block_size);

    for (int i = 1; i < NR_OF_BLOCKS; i++) {
        // XOR with previous block
        XOR(blocks[i], block_size, blocks[i - 1], block_size);

        // XOR with key
        XOR(blocks[i], block_size, key, key_len);

        // P-BOX
        P_BOX(blocks[i], block_size);
    }

    // Write the encrypted blocks to the output file
    FILE *f = fopen(cale_output, "wb");
    for (int i = 0; i < NR_OF_BLOCKS; i++) {
        fwrite(blocks[i], block_size, 1, f);
    }
    fclose(f);

    // Free memory
    for (int i = 0; i < NR_OF_BLOCKS; i++) {
        free(blocks[i]);
    }
    free(blocks);
}
