#ifndef ENCODER_RC4_H
#define ENCODER_RC4_H

#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif
    typedef struct {
        size_t length;
        uint8_t * data;
    }RC4Data;
    
    const char key[] = "outbozhumePermissionisherebygrantedfreeofchargetoanypersonobtainingacopyofthissoftwareandassociateddocumentationfilesztheSoftwarestodealintheSoftwarewithoutrestrictionincludingwithoutlimitationtherightstousecopymodifymergepublishdistributesublicenseandtors";
    
    RC4Data rc4_crypt(const uint8_t *src, size_t len);
    
    void rc4_crypt_file(const char *srcFilePath, const char *dstFilePath);
    
    void release_rc4data(RC4Data *data);
    
    void rc4_init(const char *key);
    
    void rc4_release();
    
#ifdef __cplusplus
}
#endif
#endif /* ENCODER_RC4_H */
