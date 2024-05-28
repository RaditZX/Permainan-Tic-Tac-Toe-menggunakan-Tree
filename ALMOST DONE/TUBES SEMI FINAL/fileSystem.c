#include "fileSystem.h"

// Fungsi untuk membaca tree dari file secara rekursif
TreeScore* readTreeFromFile(FILE *file) {
    char buffer[5];

    // Membaca penanda untuk node kosong
    fread(buffer, sizeof(char), 4, file);
    buffer[4] = '\0'; // Menambahkan null terminator

    if (strcmp(buffer, "NULL") == 0) {
        // Jika penanda adalah "NULL", kembalikan NULL
        return NULL;
    } else {
        // Mundur 4 byte karena kita menganggap ini bukan NULL
        fseek(file, -4, SEEK_CUR);
    }

    // Alokasi memori untuk node baru
    TreeScore *node = (TreeScore *)malloc(sizeof(TreeScore));
    if (node == NULL) {
        perror("Failed to allocate memory");
        exit(1);
    }

    // Membaca data node dari file
    fread(node, sizeof(TreeScore), 1, file);

    // Rekursi untuk membaca anak kiri dan kanan
    node->left = readTreeFromFile(file);
    node->right = readTreeFromFile(file);

    return node;
}

// Fungsi untuk memuat binary tree dari file
TreeScore* loadBinaryTree(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    TreeScore *root = readTreeFromFile(file);

    fclose(file);

    return root;
}

// Fungsi untuk menyimpan tree ke file secara rekursif
void saveTreeToFile(TreeScore *root, FILE *file) {
    if (root == NULL) {
        // Menulis indikator node kosong
        fwrite("NULL", sizeof(char), 4, file);
        return;
    }
    
    // Menulis data dari node saat ini
    fwrite(root, sizeof(TreeScore), 1, file);

    // Rekursi ke node kiri dan kanan
    saveTreeToFile(root->left, file);
    saveTreeToFile(root->right, file);
}

// Fungsi untuk menyimpan binary tree ke file
void saveBinaryTree(TreeScore *root, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    saveTreeToFile(root, file);

    fclose(file);
}


void saveTreeTimeToFile(TreeTime *root, FILE *file) {
    if (root == NULL) {
        // Menulis indikator node kosong
        fwrite("NULL", sizeof(char), 4, file);
        return;
    }
    
    // Menulis data dari node saat ini
    fwrite(root, sizeof(TreeTime), 1, file);

    // Rekursi ke node kiri dan kanan
    saveTreeTimeToFile(root->left, file);
    saveTreeTimeToFile(root->right, file);
}

void saveBinaryTreeTime(TreeTime *root, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    saveTreeTimeToFile(root, file);

    fclose(file);
}

TreeTime* readTreeTimeFromFile(FILE *file) {
    char buffer[5];

    // Membaca penanda untuk node kosong
    fread(buffer, sizeof(char), 4, file);
    buffer[4] = '\0'; // Menambahkan null terminator

    if (strcmp(buffer, "NULL") == 0) {
        // Jika penanda adalah "NULL", kembalikan NULL
        return NULL;
    } else {
        // Mundur 4 byte karena kita menganggap ini bukan NULL
        fseek(file, -4, SEEK_CUR);
    }

    // Alokasi memori untuk node baru
    TreeTime *node = (TreeTime *)malloc(sizeof(TreeTime));
    if (node == NULL) {
        perror("Failed to allocate memory");
        exit(1);
    }

    // Membaca data node dari file
    fread(node, sizeof(TreeTime), 1, file);

    // Rekursi untuk membaca anak kiri dan kanan
    node->left = readTreeTimeFromFile(file);
    node->right = readTreeTimeFromFile(file);

    return node;
}

TreeTime* loadBinaryTreeTime(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    TreeTime *root = readTreeTimeFromFile(file);

    fclose(file);

    return root;
}


