//
//  main.cpp
//  encoder
//
//  Created by olivine on 2017/3/3.
//  Copyright © 2017 olivine. All rights reserved.
//

#include <unistd.h>
#include <iostream>
#include "rc4.h"
//#include "cbccryptor.h"

using namespace std;

extern const char key[] ;

const char* options = "::r:h:d:p:i:o:s";

int main(int argc, const char * argv[]) {
    int ret = -1;
    char *pwd = nullptr ,*srcFilePath =nullptr,*dstFilePath =nullptr,*source =nullptr;
    while((ret = getopt(argc, (char *const*)(argv), options))!=-1) {
        switch (ret) {
            case 'h' : {
                cout<<"-h show help"<<endl
                //                <<"-d [argv] choose encryption algorithm , support rc4 , aes-ebc , aes-cbc"<<endl
                <<"-p [argv] set password using encryption"<<endl
                <<"-i [argv] set input file path"<<endl
                <<"-o [argv] set output file path"<<endl
                <<"-s [argv] set input string to encrypt , if use file as input don't use this"<<endl;
                return 0;
            }
            case 'p': {
                size_t len = strlen(optarg);
                pwd = (char*)malloc(sizeof(char)*(len+1));
                strcpy(pwd, optarg);
                pwd[len] = '\0';
                break;
            }
            case 'i': {
                size_t len = strlen(optarg);
                srcFilePath = (char*)malloc(sizeof(char)*(len+1));
                strcpy(srcFilePath, optarg);
                srcFilePath[len] = '\0';
                break;
            }
            case 'o': {
                size_t len = strlen(optarg);
                dstFilePath = (char*)malloc(sizeof(char)*(len+1));
                strcpy(dstFilePath, optarg);
                dstFilePath[len] = '\0';
                break;
            }
            case 'c': {
                size_t len = strlen(optarg);
                source = (char*)malloc(sizeof(char)*(len+1));
                strcpy(source, optarg);
                source[len] = '\0';
                break;
            }
            case '?': {
                cout<<" unrecognized option:"<<(char)ret<<", process closed"<<endl;
                break;
            }
            case ':' :{
                cout<<"option:"<<(char)ret<<" missing argument"<<endl;
                break;
            }
            default:
                break;
        }
    }
    //if no key input, use default key
    if(pwd==nullptr) {
        cout<<"using default key"<<endl;
    }
    rc4_init(key);
    //if no cryptor choose, use default —— RC4
    if(srcFilePath!=nullptr) {
        if(dstFilePath==nullptr) {
            char *p = strrchr(srcFilePath, '/')+1;
            size_t l1 = strlen(p);
            char out_Dir[] = "~";
            size_t l2 = strlen(out_Dir);
            dstFilePath = (char *)malloc(sizeof(char)*(strlen(srcFilePath)+l2+1));
            strlcpy(dstFilePath, srcFilePath, strlen(srcFilePath)-l1+1);
            strcat(dstFilePath,out_Dir);
            strcat(dstFilePath, p);
        }
        rc4_crypt_file(srcFilePath, dstFilePath);
    } else if(source!=nullptr) {
        cout<<"source:"<<source<<endl;
        RC4Data rc4data = rc4_crypt((const uint8_t*)source,strlen(source));
        cout<<"end:"<<rc4data.data<<endl;
        release_rc4data(&rc4data);
    }
    rc4_release();
    cout<<"cryption finish!"<<endl;
    return 0;
}
