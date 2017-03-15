#include "rc4.h"
#include <assert.h>
#include <fstream>

using namespace std;

static char *s_box = nullptr;

RC4Data rc4_crypt(const uint8_t *src, size_t len) {
    assert(s_box != nullptr);
    assert(src != nullptr);

    size_t box_Len = strlen(s_box);
    uint8_t *mask = (uint8_t *) malloc(sizeof(uint8_t) * box_Len);
    memcpy(mask,s_box,box_Len);
    size_t m_Len = box_Len;
    uint8_t *data = (uint8_t *) malloc(sizeof(uint8_t) * len);

    int i = 0, j = 0, t = 0;
    uint8_t tmp = 0;
    for (int k = 0; k < len; k++) {
        i = (i + 1) % m_Len;
        j = (j + mask[i]) % m_Len;
        tmp = mask[i];
        mask[i] = mask[j];
        mask[j] = tmp;
        t = (mask[i] + mask[j]) % m_Len;
        data[k]= src[k]^mask[t];
    }
    free(mask);
    return (RC4Data) {len,data};
}

void rc4_crypt_file(const char *srcFilePath, const char *dstFilePath) {
    ifstream is;
    is.open(srcFilePath, ios::binary);
    if (!is.is_open()) {
        printf("open file %s failed\n", srcFilePath);
        return;
    }
    ofstream os;
    os.open(dstFilePath, ios::out | ios::in | ios::trunc | ios::binary);
    if (!os.is_open()) {
        printf("open file %s failed\n", dstFilePath);
        return;
    }
    char buffer[1024];
    while (!is.eof()) {
        is.read(buffer, 1024);
        streamsize len = is.gcount();
        RC4Data rc4Data = rc4_crypt((const uint8_t *) buffer, (size_t) len);
        os.write((char *)rc4Data.data, len);
        release_rc4data(&rc4Data);
    }
    is.close();
    os.close();
}

void rc4_init(const char *key) {
    assert(s_box == nullptr);
    size_t len = strlen(key);
    s_box = (char *) malloc(sizeof(char) * (len + 1));

    char tmp = 0;
    int p = 0;
    for (int i = 0; i < len; i++) {
        s_box[i] = (char) i;
    }
    s_box[len] = '\0';

    for (int i = 0; i < len; i++) {
        p = (p + s_box[i] + key[i]) % len;
        tmp = s_box[i];
        s_box[i] = s_box[p];
        s_box[p] = tmp;
    }
}

void release_rc4data(RC4Data *data) {
    assert(data != nullptr);
    free((void *) data->data);
}

void rc4_release() {
    assert(s_box != nullptr);
    free(s_box);
}
