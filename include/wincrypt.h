/*
 * Copyright (C) 2002 Travis Michielsen
 * Copyright (C) 2004-2005 Juan Lang
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef __WINE_WINCRYPT_H
#define __WINE_WINCRYPT_H

#ifdef __cplusplus
extern "C" {
#endif

/* some typedefs for function parameters */
typedef unsigned int ALG_ID;
typedef unsigned long HCRYPTPROV;
typedef unsigned long HCRYPTKEY;
typedef unsigned long HCRYPTHASH;
typedef void *HCERTSTORE;
typedef void *HCRYPTMSG;

/* CSP Structs */

typedef struct _PROV_ENUMALGS {
  ALG_ID aiAlgid;
  DWORD  dwBitLen;
  DWORD  dwNameLen;
  CHAR   szName[20];
} PROV_ENUMALGS;

typedef struct _PROV_ENUMALGS_EX {
  ALG_ID aiAlgid;
  DWORD  dwDefaultLen;
  DWORD  dwMinLen;
  DWORD  dwMaxLen;
  DWORD  dwProtocols;
  DWORD  dwNameLen;
  CHAR   szName[20];
  DWORD  dwLongNameLen;
  CHAR   szLongName[40];
} PROV_ENUMALGS_EX;

#define SCHANNEL_MAC_KEY 0
#define SCHANNEL_ENC_KEY 1

typedef struct _SCHANNEL_ALG {
  DWORD  dwUse;
  ALG_ID Algid;
  DWORD  cBits;
  DWORD  dwFlags;
  DWORD  dwReserved;
} SCHANNEL_ALG, *PSCHANNEL_ALG;

typedef struct _HMAC_INFO {
  ALG_ID HashAlgid;
  BYTE*  pbInnerString;
  DWORD  cbInnerString;
  BYTE*  pbOuterString;
  DWORD  cbOuterString;
} HMAC_INFO, *PHMAC_INFO;
		
typedef struct _CRYPTOAPI_BLOB {
  DWORD    cbData;
  BYTE*    pbData;
} CRYPT_INTEGER_BLOB,  *PCRYPT_INTEGER_BLOB,
  CRYPT_UINT_BLOB,     *PCRYPT_UINT_BLOB,
  CRYPT_OBJID_BLOB,    *PCRYPT_OBJID_BLOB,
  CERT_NAME_BLOB,      *PCERT_NAME_BLOB,
  CERT_RDN_VALUE_BLOB, *PCERT_RDN_VALUE_BLOB,
  CERT_BLOB,           *PCERT_BLOB,
  CRL_BLOB,            *PCRL_BLOB,
  DATA_BLOB,           *PDATA_BLOB,
  CRYPT_DATA_BLOB,     *PCRYPT_DATA_BLOB,
  CRYPT_HASH_BLOB,     *PCRYPT_HASH_BLOB,
  CRYPT_DIGEST_BLOB,   *PCRYPT_DIGEST_BLOB,
  CRYPT_DER_BLOB,      *PCRYPT_DER_BLOB,
  CRYPT_ATTR_BLOB,     *PCRYPT_ATTR_BLOB;

typedef struct _CRYPTPROTECT_PROMPTSTRUCT{
  DWORD   cbSize;
  DWORD   dwPromptFlags;
  HWND    hwndApp;
  LPCWSTR szPrompt;
} CRYPTPROTECT_PROMPTSTRUCT, *PCRYPTPROTECT_PROMPTSTRUCT;

typedef struct _CRYPT_ALGORITHM_IDENTIFIER {
  LPSTR            pszObjId;
  CRYPT_OBJID_BLOB Parameters;
} CRYPT_ALGORITHM_IDENTIFIER, *PCRYPT_ALGORITHM_IDENTIFIER;

typedef struct _CRYPT_ATTRIBUTE_TYPE_VALUE {
  LPSTR               pszObjId;
  CRYPT_OBJID_BLOB    Value;
} CRYPT_ATTRIBUTE_TYPE_VALUE, *PCRYPT_ATTRIBUTE_TYPE_VALUE;

typedef struct _PUBLICKEYSTRUC {
    BYTE   bType;
    BYTE   bVersion;
    WORD   reserved;
    ALG_ID aiKeyAlg;
} BLOBHEADER, PUBLICKEYSTRUC;

typedef struct _RSAPUBKEY {
    DWORD   magic;
    DWORD   bitlen;
    DWORD   pubexp;
} RSAPUBKEY;

typedef struct _CRYPT_BIT_BLOB {
    DWORD cbData;
    BYTE  *pbData;
    DWORD cUnusedBits;
} CRYPT_BIT_BLOB, *PCRYPT_BIT_BLOB;

typedef struct _CERT_PUBLIC_KEY_INFO {
    CRYPT_ALGORITHM_IDENTIFIER Algorithm;
    CRYPT_BIT_BLOB             PublicKey;
} CERT_PUBLIC_KEY_INFO, *PCERT_PUBLIC_KEY_INFO;

typedef struct _CERT_EXTENSION {
    LPSTR               pszObjId;
    BOOL                fCritical;
    CRYPT_OBJID_BLOB    Value;
} CERT_EXTENSION, *PCERT_EXTENSION;

typedef struct _CERT_EXTENSIONS {
    DWORD           cExtension;
    PCERT_EXTENSION rgExtension;
} CERT_EXTENSIONS, *PCERT_EXTENSIONS;

typedef struct _CERT_INFO {
    DWORD                      dwVersion;
    CRYPT_INTEGER_BLOB         SerialNumber;
    CRYPT_ALGORITHM_IDENTIFIER SignatureAlgorithm;
    CERT_NAME_BLOB             Issuer;
    FILETIME                   NotBefore;
    FILETIME                   NotAfter;
    CERT_NAME_BLOB             Subject;
    CERT_PUBLIC_KEY_INFO       SubjectPublicKeyInfo;
    CRYPT_BIT_BLOB             IssuerUniqueId;
    CRYPT_BIT_BLOB             SubjectUniqueId;
    DWORD                      cExtension;
    PCERT_EXTENSION            rgExtension;
} CERT_INFO, *PCERT_INFO;

typedef struct _CERT_RDN_ATTR {
    LPSTR               pszObjId;
    DWORD               dwValueType;
    CERT_RDN_VALUE_BLOB Value;
} CERT_RDN_ATTR, *PCERT_RDN_ATTR;

typedef struct _CERT_RDN {
    DWORD          cRDNAttr;
    PCERT_RDN_ATTR rgRDNAttr;
} CERT_RDN, *PCERT_RDN;

typedef struct _CERT_NAME_INFO {
    DWORD     cRDN;
    PCERT_RDN rgRDN;
} CERT_NAME_INFO, *PCERT_NAME_INFO;

typedef struct _CERT_NAME_VALUE {
    DWORD               dwValueType;
    CERT_RDN_VALUE_BLOB Value;
} CERT_NAME_VALUE, *PCERT_NAME_VALUE;

typedef struct _CERT_ENCRYPTED_PRIVATE_KEY_INFO {
    CRYPT_ALGORITHM_IDENTIFIER EncryptionAlgorithm;
    CRYPT_DATA_BLOB            EncryptedPrivateKey;
} CERT_ENCRYPTED_PRIVATE_KEY_INFO, *PCERT_ENCRYPTED_PRIVATE_KEY_INFO;

typedef struct _CERT_AUTHORITY_KEY_ID_INFO {
    CRYPT_DATA_BLOB    KeyId;
    CERT_NAME_BLOB     CertIssuer;
    CRYPT_INTEGER_BLOB CertSerialNumber;
} CERT_AUTHORITY_KEY_ID_INFO, *PCERT_AUTHORITY_KEY_ID_INFO;

typedef struct _CERT_PRIVATE_KEY_VALIDITY {
    FILETIME NotBefore;
    FILETIME NotAfter;
} CERT_PRIVATE_KEY_VALIDITY, *PCERT_PRIVATE_KEY_VALIDITY;

typedef struct _CERT_KEY_ATTRIBUTES_INFO {
    CRYPT_DATA_BLOB            KeyId;
    CRYPT_BIT_BLOB             IntendedKeyUsage;
    PCERT_PRIVATE_KEY_VALIDITY pPrivateKeyUsagePeriod;
} CERT_KEY_ATTRIBUTES_INFO, *PCERT_KEY_ATTRIBUTES_INFO;

typedef struct _CERT_POLICY_ID {
    DWORD  cCertPolicyElementId;
    LPSTR *rgbszCertPolicyElementId;
} CERT_POLICY_ID, *PCERT_POLICY_ID;

typedef struct _CERT_KEY_USAGE_RESTRICTION_INFO {
    DWORD           cCertPolicyId;
    PCERT_POLICY_ID rgCertPolicyId;
    CRYPT_BIT_BLOB  RestrictedKeyUsage;
} CERT_KEY_USAGE_RESTRICTION_INFO, *PCERT_KEY_USAGE_RESTRICTION_INFO;

typedef struct _CERT_OTHER_NAME {
    LPSTR            pszObjId;
    CRYPT_OBJID_BLOB Value;
} CERT_OTHER_NAME, *PCERT_OTHER_NAME;

typedef struct _CERT_ALT_NAME_ENTRY {
    DWORD dwAltNameChoice;
    union {
        PCERT_OTHER_NAME pOtherName;
        LPWSTR           pwszRfc822Name;
        LPWSTR           pwszDNSName;
        CERT_NAME_BLOB   DirectoryName;
        LPWSTR           pwszURL;
        CRYPT_DATA_BLOB  IPaddress;
        LPSTR            pszRegisteredID;
    } DUMMYUNIONNAME;
} CERT_ALT_NAME_ENTRY, *PCERT_ALT_NAME_ENTRY;

typedef struct _CERT_ALT_NAME_INFO {
    DWORD                cAltEntry;
    PCERT_ALT_NAME_ENTRY rgAltEntry;
} CERT_ALT_NAME_INFO, *PCERT_ALT_NAME_INFO;

typedef struct _CERT_CONTEXT {
    DWORD      dwCertEncodingType;
    BYTE       *pbCertEncoded;
    DWORD      cbCertEncoded;
    PCERT_INFO pCertInfo;
    HCERTSTORE hCertStore;
} CERT_CONTEXT, *PCERT_CONTEXT;
typedef const CERT_CONTEXT *PCCERT_CONTEXT;

typedef struct _CRL_ENTRY {
    CRYPT_INTEGER_BLOB SerialNumber;
    FILETIME           RevocationDate;
    DWORD              cExtension;
    PCERT_EXTENSION    rgExtension;
} CRL_ENTRY, *PCRL_ENTRY;

typedef struct _CRL_INFO {
    DWORD           dwVersion;
    CRYPT_ALGORITHM_IDENTIFIER SignatureAlgorithm;
    CERT_NAME_BLOB  Issuer;
    FILETIME        ThisUpdate;
    FILETIME        NextUpdate;
    DWORD           cCRLEntry;
    PCRL_ENTRY      rgCRLEntry;
    DWORD           cExtension;
    PCERT_EXTENSION rgExtension;
} CRL_INFO, *PCRL_INFO;

typedef struct _CRL_CONTEXT {
    DWORD      dwCertEncodingType;
    BYTE      *pbCrlEncoded;
    DWORD      cbCrlEncoded;
    PCRL_INFO  pCrlInfo;
    HCERTSTORE hCertStore;
} CRL_CONTEXT, *PCRL_CONTEXT;
typedef const CRL_CONTEXT *PCCRL_CONTEXT;

typedef struct _VTableProvStruc {
    DWORD    Version;
    FARPROC  pFuncVerifyImage;
    FARPROC  pFuncReturnhWnd;
    DWORD    dwProvType;
    BYTE    *pbContextInfo;
    DWORD    cbContextInfo;
    LPSTR    pszProvName;
} VTableProvStruc, *PVTableProvStruc;

typedef struct _CRYPT_ATTRIBUTE {
    LPSTR           pszObjId;
    DWORD           cValue;
    CRYPT_DATA_BLOB rgValue;
} CRYPT_ATTRIBUTE, *PCRYPT_ATTRIBUTE;

typedef struct _CRYPT_ATTRIBUTES {
    DWORD            cAttr;
    PCRYPT_ATTRIBUTE rgAttr;
} CRYPT_ATTRIBUTES, *PCRYPT_ATTRIBUTES;

typedef struct _CERT_PRIVATE_KEY_INFO {
    DWORD                      Version;
    CRYPT_ALGORITHM_IDENTIFIER Algorithm;
    CRYPT_DER_BLOB             PrivateKey;
    PCRYPT_ATTRIBUTES          pAttributes;
} CERT_PRIVATE_KEY_INFO, *PCERT_PRIVATE_KEY_INFO;

typedef struct _CTL_USAGE {
    DWORD  cUsageIdentifier;
    LPSTR *rgpszUsageIdentifier;
} CTL_USAGE, *PCTL_USAGE, CERT_ENHKEY_USAGE, *PCERT_ENHKEY_USAGE;

typedef struct _CTL_ENTRY {
    CRYPT_DATA_BLOB  SubjectIdentifier;
    DWORD            cAttribute;
    PCRYPT_ATTRIBUTE rgAttribute;
} CTL_ENTRY, *PCTL_ENTRY;

typedef struct _CTL_INFO {
    DWORD                      dwVersion;
    CTL_USAGE                  SubjectUsage;
    CRYPT_DATA_BLOB            ListIdentifier;
    CRYPT_INTEGER_BLOB         SequenceNumber;
    FILETIME                   ThisUpdate;
    FILETIME                   NextUpdate;
    CRYPT_ALGORITHM_IDENTIFIER SubjectAlgorithm;
    DWORD                      cCTLEntry;
    PCTL_ENTRY                 rgCTLEntry;
    DWORD                      cExtension;
    PCERT_EXTENSION            rgExtension;
} CTL_INFO, *PCTL_INFO;

typedef struct _CTL_CONTEXT {
    DWORD      dwMsgAndCertEncodingType;
    BYTE      *pbCtlEncoded;
    DWORD      cbCtlEncoded;
    PCTL_INFO  pCtlInfo;
    HCERTSTORE hCertStore;
    HCRYPTMSG  hCryptMsg;
    BYTE      *pbCtlContext;
    DWORD      cbCtlContext;
} CTL_CONTEXT, *PCTL_CONTEXT;
typedef const CTL_CONTEXT *PCCTL_CONTEXT;

typedef struct _CMSG_SIGNER_INFO {
    DWORD                      dwVersion;
    CERT_NAME_BLOB             Issuer;
    CRYPT_INTEGER_BLOB         SerialNumber;
    CRYPT_ALGORITHM_IDENTIFIER HashAlgorithm;
    CRYPT_ALGORITHM_IDENTIFIER HashEncryptionAlgorithm;
    CRYPT_DATA_BLOB            EncryptedHash;
    CRYPT_ATTRIBUTES           AuthAttrs;
    CRYPT_ATTRIBUTES           UnauthAttrs;
} CMSG_SIGNER_INFO, *PCMSG_SIGNER_INFO;

typedef struct _CERT_REVOCATION_CRL_INFO {
    DWORD         cbSize;
    PCCRL_CONTEXT pBaseCrlContext;
    PCCRL_CONTEXT pDeltaCrlContext;
    PCRL_ENTRY    pCrlEntry;
    BOOL          fDeltaCrlEntry;
} CERT_REVOCATION_CRL_INFO, *PCERT_REVOCATION_CRL_INFO;

typedef struct _CERT_REVOCATION_INFO {
    DWORD                     cbSize;
    DWORD                     dwRevocationResult;
    LPCSTR                    pszRevocationOid;
    LPVOID                    pvOidSpecificInfo;
    BOOL                      fHasFreshnessTime;
    DWORD                     dwFreshnessTime;
    PCERT_REVOCATION_CRL_INFO pCrlInfo;
} CERT_REVOCATION_INFO, *PCERT_REVOCATION_INFO;

typedef struct _CERT_TRUST_LIST_INFO {
    DWORD         cbSize;
    PCTL_ENTRY    pCtlEntry;
    PCCTL_CONTEXT pCtlContext;
} CERT_TRUST_LIST_INFO, *PCERT_TRUST_LIST_INFO;

typedef struct _CERT_TRUST_STATUS {
    DWORD dwErrorStatus;
    DWORD dwInfoStatus;
} CERT_TRUST_STATUS, *PCERT_TRUST_STATUS;

typedef struct _CERT_CHAIN_ELEMENT {
    DWORD                 cbSize;
    PCCERT_CONTEXT        pCertContext;
    CERT_TRUST_STATUS     TrustStatus;
    PCERT_REVOCATION_INFO pRevocationInfo;
    PCERT_ENHKEY_USAGE    pIssuanceUsage;
    PCERT_ENHKEY_USAGE    pApplicationUsage;
    LPCWSTR               pwszExtendedErrorInfo;
} CERT_CHAIN_ELEMENT, *PCERT_CHAIN_ELEMENT;

typedef struct _CERT_SIMPLE_CHAIN {
    DWORD                 cbSize;
    CERT_TRUST_STATUS     TrustStatus;
    DWORD                 cElement;
    PCERT_CHAIN_ELEMENT  *rgpElement;
    PCERT_TRUST_LIST_INFO pTrustListInfo;
    BOOL                  fHasRevocationFreshnessTime;
    DWORD                 dwRevocationFreshnessTime;
} CERT_SIMPLE_CHAIN, *PCERT_SIMPLE_CHAIN;

typedef struct _CERT_CHAIN_CONTEXT CERT_CHAIN_CONTEXT, *PCERT_CHAIN_CONTEXT;
typedef const CERT_CHAIN_CONTEXT *PCCERT_CHAIN_CONTEXT;

struct _CERT_CHAIN_CONTEXT {
    DWORD                 cbSize;
    CERT_TRUST_STATUS     TrustStatus;
    DWORD                 cChain;
    PCERT_SIMPLE_CHAIN   *rgpChain;
    DWORD                 cLowerQualityChainContext;
    PCCERT_CHAIN_CONTEXT *rgbLowerQualityChainContext;
    BOOL                  fHasRevocationFreshnessTime;
    DWORD                 dwRevocationFreshnessTime;
};

typedef struct _CERT_CHAIN_POLICY_PARA {
    DWORD cbSize;
    DWORD dwFlags;
    void *pvExtraPolicyPara;
} CERT_CHAIN_POLICY_PARA, *PCERT_CHAIN_POLICY_PARA;

typedef struct _CERT_CHAIN_POLICY_STATUS {
    DWORD cbSize;
    DWORD dwError;
    LONG  lChainIndex;
    LONG  lElementIndex;
    void *pvExtraPolicyStatus;
} CERT_CHAIN_POLICY_STATUS, *PCERT_CHAIN_POLICY_STATUS;

typedef struct _CERT_SYSTEM_STORE_INFO {
    DWORD cbSize;
} CERT_SYSTEM_STORE_INFO, *PCERT_SYSTEM_STORE_INFO;

typedef struct _CERT_PHYSICAL_STORE_INFO {
    DWORD           cbSize;
    LPSTR           pszOpenStoreProvider;
    DWORD           dwOpenEncodingType;
    DWORD           dwOpenFlags;
    CRYPT_DATA_BLOB OpenParameters;
    DWORD           dwFlags;
    DWORD           dwPriority;
} CERT_PHYSICAL_STORE_INFO, *PCERT_PHYSICAL_STORE_INFO;

typedef struct _CERT_SYSTEM_STORE_RELOCATE_PARA {
    union {
        HKEY  hKeyBase;
        VOID *pvBase;
    } DUMMYUNIONNAME;
    union {
        void   *pvSystemStore;
        LPCSTR  pszSystemStore;
        LPCWSTR pwszSystemStore;
    } DUMMYUNIONNAME2;
} CERT_SYSTEM_STORE_RELOCATE_PARA, *PCERT_SYSTEM_STORE_RELOCATE_PARA;

typedef BOOL (WINAPI *PFN_CERT_ENUM_SYSTEM_STORE_LOCATION)(
 LPCWSTR pwszStoreLocation, DWORD dwFlags, void *pvReserved, void *pvArg);

typedef BOOL (WINAPI *PFN_CERT_ENUM_SYSTEM_STORE)(const void *pvSystemStore,
 DWORD dwFlags, PCERT_SYSTEM_STORE_INFO pStoreInfo, void *pvReserved,
 void *pvArg);

typedef BOOL (WINAPI *PFN_CERT_ENUM_PHYSICAL_STORE)(const void *pvSystemStore,
 DWORD dwFlags, LPCWSTR pwszStoreName, PCERT_PHYSICAL_STORE_INFO pStoreInfo,
 void *pvReserved, void *pvArg);

/* Encode/decode object */
typedef LPVOID (WINAPI *PFN_CRYPT_ALLOC)(size_t cbsize);
typedef VOID   (WINAPI *PFN_CRYPT_FREE)(LPVOID pv);

typedef struct _CRYPT_ENCODE_PARA {
    DWORD           cbSize;
    PFN_CRYPT_ALLOC pfnAlloc;
    PFN_CRYPT_FREE  pfnFree;
} CRYPT_ENCODE_PARA, *PCRYPT_ENCODE_PARA;

typedef struct _CRYPT_DECODE_PARA {
    DWORD           cbSize;
    PFN_CRYPT_ALLOC pfnAlloc;
    PFN_CRYPT_FREE  pfnFree;
} CRYPT_DECODE_PARA, *PCRYPT_DECODE_PARA;

/* Algorithm IDs */

#define GET_ALG_CLASS(x)                (x & (7 << 13))
#define GET_ALG_TYPE(x)                 (x & (15 << 9))
#define GET_ALG_SID(x)                  (x & (511))

/* Algorithm Classes */
#define ALG_CLASS_ANY                   (0)
#define ALG_CLASS_SIGNATURE             (1 << 13)
#define ALG_CLASS_MSG_ENCRYPT           (2 << 13)
#define ALG_CLASS_DATA_ENCRYPT          (3 << 13)
#define ALG_CLASS_HASH                  (4 << 13)
#define ALG_CLASS_KEY_EXCHANGE          (5 << 13)
/* Algorithm types */
#define ALG_TYPE_ANY                    (0)
#define ALG_TYPE_DSS                    (1 << 9)
#define ALG_TYPE_RSA                    (2 << 9)
#define ALG_TYPE_BLOCK                  (3 << 9)
#define ALG_TYPE_STREAM                 (4 << 9)
#define ALG_TYPE_DH                     (5 << 9)
#define ALG_TYPE_SECURECHANNEL          (6 << 9)

/* SIDs */
#define ALG_SID_ANY                     (0)
/* RSA SIDs */
#define ALG_SID_RSA_ANY                 0
#define ALG_SID_RSA_PKCS                1
#define ALG_SID_RSA_MSATWORK            2
#define ALG_SID_RSA_ENTRUST             3
#define ALG_SID_RSA_PGP                 4
/* DSS SIDs */
#define ALG_SID_DSS_ANY                 0
#define ALG_SID_DSS_PKCS                1
#define ALG_SID_DSS_DMS                 2

/* DES SIDs */
#define ALG_SID_DES                     1
#define ALG_SID_3DES                    3
#define ALG_SID_DESX                    4
#define ALG_SID_IDEA                    5
#define ALG_SID_CAST                    6
#define ALG_SID_SAFERSK64               7
#define ALG_SID_SAFERSK128              8
#define ALG_SID_3DES_112                9
/* RC2 SIDs */
#define ALG_SID_RC4                     1
#define ALG_SID_RC2                     2
#define ALG_SID_SEAL                    2
/* Hash SIDs */
#define ALG_SID_MD2                     1
#define ALG_SID_MD4                     2
#define ALG_SID_MD5                     3
#define ALG_SID_SHA                     4
#define ALG_SID_MAC                     5
#define ALG_SID_RIPEMD                  6
#define ALG_SID_RIPEMD160               7
#define ALG_SID_SSL3SHAMD5              8
#define ALG_SID_HMAC                    9
#define ALG_SID_TLS1PRF                10
/* SCHANNEL SIDs */
#define ALG_SID_SSL3_MASTER             1
#define ALG_SID_SCHANNEL_MASTER_HASH    2
#define ALG_SID_SCHANNEL_MAC_KEY        3
#define ALG_SID_PCT1_MASTER             4
#define ALG_SID_SSL2_MASTER             5
#define ALG_SID_TLS1_MASTER             6
#define ALG_SID_SCHANNEL_ENC_KEY        7

/* Algorithm Definitions */
#define CALG_MD2                  (ALG_CLASS_HASH         | ALG_TYPE_ANY           | ALG_SID_MD2)
#define CALG_MD4                  (ALG_CLASS_HASH         | ALG_TYPE_ANY           | ALG_SID_MD4)
#define CALG_MD5                  (ALG_CLASS_HASH         | ALG_TYPE_ANY           | ALG_SID_MD5)
#define CALG_SHA                  (ALG_CLASS_HASH         | ALG_TYPE_ANY           | ALG_SID_SHA)
#define CALG_MAC                  (ALG_CLASS_HASH         | ALG_TYPE_ANY           | ALG_SID_MAC)
#define CALG_SSL3_SHAMD5          (ALG_CLASS_HASH         | ALG_TYPE_ANY           | ALG_SID_SSL3SHAMD5)
#define CALG_HMAC                 (ALG_CLASS_HASH         | ALG_TYPE_ANY           | ALG_SID_HMAC)
#define CALG_TLS1PRF              (ALG_CLASS_HASH         | ALG_TYPE_ANY           | ALG_SID_TLS1PRF)
#define CALG_RSA_SIGN             (ALG_CLASS_SIGNATURE    | ALG_TYPE_RSA           | ALG_SID_RSA_ANY)
#define CALG_DSS_SIGN             (ALG_CLASS_SIGNATURE    | ALG_TYPE_DSS           | ALG_SID_DSS_ANY)
#define CALG_RSA_KEYX             (ALG_CLASS_KEY_EXCHANGE | ALG_TYPE_RSA           | ALG_SID_RSA_ANY)
#define CALG_DES                  (ALG_CLASS_DATA_ENCRYPT | ALG_TYPE_BLOCK         | ALG_SID_DES)
#define CALG_RC2                  (ALG_CLASS_DATA_ENCRYPT | ALG_TYPE_BLOCK         | ALG_SID_RC2)
#define CALG_3DES                 (ALG_CLASS_DATA_ENCRYPT | ALG_TYPE_BLOCK         | ALG_SID_3DES)
#define CALG_3DES_112             (ALG_CLASS_DATA_ENCRYPT | ALG_TYPE_BLOCK         | ALG_SID_3DES_112)
#define CALG_RC4                  (ALG_CLASS_DATA_ENCRYPT | ALG_TYPE_STREAM        | ALG_SID_RC4)
#define CALG_SEAL                 (ALG_CLASS_DATA_ENCRYPT | ALG_TYPE_STREAM        | ALG_SID_SEAL)
#define CALG_SSL3_MASTER          (ALG_CLASS_MSG_ENCRYPT  | ALG_TYPE_SECURECHANNEL | ALG_SID_SSL3_MASTER)
#define CALG_SCHANNEL_MASTER_HASH (ALG_CLASS_MSG_ENCRYPT  | ALG_TYPE_SECURECHANNEL | ALG_SID_SCHANNEL_MASTER_HASH)
#define CALG_SCHANNEL_MAC_KEY     (ALG_CLASS_MSG_ENCRYPT  | ALG_TYPE_SECURECHANNEL | ALG_SID_SCHANNEL_MAC_KEY)
#define CALG_SCHANNEL_ENC_KEY     (ALG_CLASS_MSG_ENCRYPT  | ALG_TYPE_SECURECHANNEL | ALG_SID_SCHANNEL_ENC_KEY)
#define CALG_PCT1_MASTER          (ALG_CLASS_MSG_ENCRYPT  | ALG_TYPE_SECURECHANNEL | ALG_SID_PCT1_MASTER)
#define CALG_SSL2_MASTER          (ALG_CLASS_MSG_ENCRYPT  | ALG_TYPE_SECURECHANNEL | ALG_SID_SSL2_MASTER)
#define CALG_TLS1_MASTER          (ALG_CLASS_MSG_ENCRYPT  | ALG_TYPE_SECURECHANNEL | ALG_SID_TLS1_MASTER)

/* Protocol Flags */
#define CRYPT_FLAG_PCT1    0x0001
#define CRYPT_FLAG_SSL2    0x0002
#define CRYPT_FLAG_SSL3    0x0004
#define CRYPT_FLAG_TLS1    0x0008
#define CRYPT_FLAG_IPSEC   0x0010
#define CRYPT_FLAG_SIGNING 0x0020

/* Provider names */
#define MS_DEF_PROV_A                            "Microsoft Base Cryptographic Provider v1.0"
#if defined(__GNUC__)
# define MS_DEF_PROV_W (const WCHAR []){ 'M','i','c','r','o','s','o','f','t',' ', \
	'B','a','s','e',' ','C','r','y','p','t','o','g','r','a','p','h','i','c',' ', \
	'P','r','o','v','i','d','e','r',' ','v','1','.','0',0 }
#elif defined(_MSC_VER)
# define MS_DEF_PROV_W      L"Microsoft Base Cryptographic Provider v1.0"
#else
static const WCHAR MS_DEF_PROV_W[] =             { 'M','i','c','r','o','s','o','f','t',' ',
	'B','a','s','e',' ','C','r','y','p','t','o','g','r','a','p','h','i','c',' ',
	'P','r','o','v','i','d','e','r',' ','v','1','.','0',0 };
#endif
#define MS_DEF_PROV                              WINELIB_NAME_AW(MS_DEF_PROV_)

#define MS_ENHANCED_PROV_A                       "Microsoft Enhanced Cryptographic Provider v1.0"
#if defined(__GNUC__)
# define MS_ENHANCED_PROV_W (const WCHAR []){ 'M','i','c','r','o','s','o','f','t',' ', \
	'E','n','h','a','n','c','e','d',' ','C','r','y','p','t','o','g','r','a','p','h','i','c',' ', \
	'P','r','o','v','i','d','e','r',' ','v','1','.','0',0 }
#elif defined(_MSC_VER)
# define MS_ENHANCED_PROV_W     L"Microsoft Enhanced Cryptographic Provider v1.0"
#else
static const WCHAR MS_ENHANCED_PROV_W[] =        { 'M','i','c','r','o','s','o','f','t',' ',
	'E','n','h','a','n','c','e','d',' ','C','r','y','p','t','o','g','r','a','p','h','i','c',' ',
	'P','r','o','v','i','d','e','r',' ','v','1','.','0',0 };
#endif
#define MS_ENHANCED_PROV                         WINELIB_NAME_AW(MS_ENHANCED_PROV_)

#define MS_STRONG_PROV_A                         "Microsoft Strong Cryptographic Provider"
#if defined(__GNUC__)
# define MS_STRONG_PROV_W (const WCHAR []){ 'M','i','c','r','o','s','o','f','t',' ', \
	'S','t','r','o','n','g',' ','C','r','y','p','t','o','g','r','a','p','h','i','c',' ', \
	'P','r','o','v','i','d','e','r',0 }
#elif defined(_MSC_VER)
# define MS_STRONG_PROV_W     L"Microsoft Strong Cryptographic Provider"
#else
static const WCHAR MS_STRONG_PROV_W[] =          { 'M','i','c','r','o','s','o','f','t',' ',
	'S','t','r','o','n','g',' ','C','r','y','p','t','o','g','r','a','p','h','i','c',' ',
	'P','r','o','v','i','d','e','r',0 };
#endif
#define MS_STRONG_PROV                           WINELIB_NAME_AW(MS_STRONG_PROV_)

#define MS_DEF_RSA_SIG_PROV_A                    "Microsoft RSA Signature Cryptographic Provider"
#if defined(__GNUC__)
# define MS_DEF_RSA_SIG_PROV_W (const WCHAR []){ 'M','i','c','r','o','s','o','f','t',' ', \
	'R','S','A',' ','S','i','g','n','a','t','u','r','e',' ', \
	'C','r','y','p','t','o','g','r','a','p','h','i','c',' ','P','r','o','v','i','d','e','r',0 }
#elif defined(_MSC_VER)
# define MS_DEF_RSA_SIG_PROV_W      L"Microsoft RSA Signature Cryptographic Provider"
#else
static const WCHAR MS_DEF_RSA_SIG_PROV_W[] =     { 'M','i','c','r','o','s','o','f','t',' ',
	'R','S','A',' ','S','i','g','n','a','t','u','r','e',' ',
	'C','r','y','p','t','o','g','r','a','p','h','i','c',' ','P','r','o','v','i','d','e','r',0 };
#endif
#define MS_DEF_RSA_SIG_PROV                      WINELIB_NAME_AW(MS_DEF_RSA_SIG_PROV_)

#define MS_DEF_RSA_SCHANNEL_PROV_A               "Microsoft RSA SChannel Cryptographic Provider"
#if defined(__GNUC__)
# define MS_DEF_RSA_SCHANNEL_PROV_W (const WCHAR []){ 'M','i','c','r','o','s','o','f','t',' ', \
	'R','S','A',' ','S','C','h','a','n','n','e','l',' ', \
	'C','r','y','p','t','o','g','r','a','p','h','i','c',' ','P','r','o','v','i','d','e','r',0 }
#elif defined(_MSC_VER)
# define MS_DEF_RSA_SCHANNEL_PROV_W     L"Microsoft RSA SChannel Cryptographic Provider"
#else
static const WCHAR MS_DEF_RSA_SCHANNEL_PROV_W[] = { 'M','i','c','r','o','s','o','f','t',' ',
	'R','S','A',' ','S','C','h','a','n','n','e','l',' ',
	'C','r','y','p','t','o','g','r','a','p','h','i','c',' ','P','r','o','v','i','d','e','r',0 };
#endif
#define MS_DEF_RSA_SCHANNEL_PROV                 WINELIB_NAME_AW(MS_DEF_RSA_SCHANNEL_PROV_)

#define MS_DEF_DSS_PROV_A                        "Microsoft Base DSS Cryptographic Provider"
#if defined(__GNUC__)
# define MS_DEF_DSS_PROV_W (const WCHAR []){ 'M','i','c','r','o','s','o','f','t',' ', \
	'B','a','s','e',' ','D','S','S',' ', \
	'C','r','y','p','t','o','g','r','a','p','h','i','c',' ','P','r','o','v','i','d','e','r',0 }
#elif defined(_MSC_VER)
# define MS_DEF_DSS_PROV_W     L"Microsoft Base DSS Cryptographic Provider"
#else
static const WCHAR MS_DEF_DSS_PROV_W[] =         { 'M','i','c','r','o','s','o','f','t',' ',
	'B','a','s','e',' ','D','S','S',' ',
	'C','r','y','p','t','o','g','r','a','p','h','i','c',' ','P','r','o','v','i','d','e','r',0 };
#endif
#define MS_DEF_DSS_PROV                          WINELIB_NAME_AW(MS_DEF_DSS_PROV_)

#define MS_DEF_DSS_DH_PROV_A                     "Microsoft Base DSS and Diffie-Hellman Cryptographic Provider"
#if defined(__GNUC__)
# define MS_DEF_DSS_DH_PROV_W (const WCHAR []){ 'M','i','c','r','o','s','o','f','t',' ', \
	'B','a','s','e',' ','D','S','S',' ','a','n','d',' ', \
	'D','i','f','f','i','e','-','H','e','l','l','m','a','n',' ', \
	'C','r','y','p','t','o','g','r','a','p','h','i','c',' ','P','r','o','v','i','d','e','r',0 }
#elif defined(_MSC_VER)
# define MS_DEF_DSS_DH_PROV_W     L"Microsoft Base DSS and Diffie-Hellman Cryptographic Provider"
#else
static const WCHAR MS_DEF_DSS_DH_PROV_W[] =      { 'M','i','c','r','o','s','o','f','t',' ',
	'B','a','s','e',' ','D','S','S',' ','a','n','d',' ',
	'D','i','f','f','i','e','-','H','e','l','l','m','a','n',' ',
	'C','r','y','p','t','o','g','r','a','p','h','i','c',' ','P','r','o','v','i','d','e','r',0 };
#endif
#define MS_DEF_DSS_DH_PROV                       WINELIB_NAME_AW(MS_DEF_DSS_DH_PROV_)

#define MS_ENH_DSS_DH_PROV_A                     "Microsoft Enhanced DSS and Diffie-Hellman Cryptographic Provider"
#if defined(__GNUC__)
# define MS_ENH_DSS_DH_PROV_W (const WCHAR []){ 'M','i','c','r','o','s','o','f','t',' ', \
	'E','n','h','a','n','c','e','d',' ','D','S','S',' ','a','n','d',' ', \
	'D','i','f','f','i','e','-','H','e','l','l','m','a','n',' ', \
	'C','r','y','p','t','o','g','r','a','p','h','i','c',' ','P','r','o','v','i','d','e','r',0 }
#elif defined(_MSC_VER)
# define MS_ENH_DSS_DH_PROV_W     L"Microsoft Enhanced DSS and Diffie-Hellman Cryptographic Provider"
#else
static const WCHAR MS_ENH_DSS_DH_PROV_W[] =      { 'M','i','c','r','o','s','o','f','t',' ',
	'E','n','h','a','n','c','e','d',' ','D','S','S',' ','a','n','d',' ',
	'D','i','f','f','i','e','-','H','e','l','l','m','a','n',' ',
	'C','r','y','p','t','o','g','r','a','p','h','i','c',' ','P','r','o','v','i','d','e','r',0 };
#endif
#define MS_ENH_DSS_DH_PROV                       WINELIB_NAME_AW(MS_ENH_DSS_DH_PROV_)

#define MS_DEF_DH_SCHANNEL_PROV_A                "Microsoft DH SChannel Cryptographic Provider"
#if defined(__GNUC__)
# define MS_DEF_DH_SCHANNEL_PROV_W (const WCHAR []){ 'M','i','c','r','o','s','o','f','t',' ', \
	'D','H',' ','S','C','h','a','n','n','e','l',' ', \
	'C','r','y','p','t','o','g','r','a','p','h','i','c',' ','P','r','o','v','i','d','e','r',0 }
#elif defined(_MSC_VER)
# define MS_DEF_DH_SCHANNEL_PROV_W     L"Microsoft DH SChannel Cryptographic Provider"
#else
static const WCHAR MS_DEF_DH_SCHANNEL_PROV_W[] = { 'M','i','c','r','o','s','o','f','t',' ',
	'D','H',' ','S','C','h','a','n','n','e','l',' ',
	'C','r','y','p','t','o','g','r','a','p','h','i','c',' ','P','r','o','v','i','d','e','r',0 };
#endif
#define MS_DEF_DH_SCHANNEL_PROV                  WINELIB_NAME_AW(MS_DEF_DH_SCHANNEL_PROV_)

#define MS_SCARD_PROV_A                          "Microsoft Base Smart Card Cryptographic Provider"
#if defined(__GNUC__)
# define MS_SCARD_PROV_W (const WCHAR []){ 'M','i','c','r','o','s','o','f','t',' ', \
	'B','a','s','e',' ','S','m','a','r','t',' ','C','a','r','d',' ', \
	'C','r','y','p','t','o','g','r','a','p','h','i','c',' ','P','r','o','v','i','d','e','r',0 }
#elif defined(_MSC_VER)
# define MS_SCARD_PROV_W     L"Microsoft Base Smart Card Cryptographic Provider"
#else
static const WCHAR MS_SCARD_PROV_W[] =           { 'M','i','c','r','o','s','o','f','t',' ',
	'B','a','s','e',' ','S','m','a','r','t',' ','C','a','r','d',' ',
	'C','r','y','p','t','o','g','r','a','p','h','i','c',' ','P','r','o','v','i','d','e','r',0 };
#endif
#define MS_SCARD_PROV                            WINELIB_NAME_AW(MS_SCARD_PROV_)

/* Key Specs*/
#define AT_KEYEXCHANGE          1
#define AT_SIGNATURE            2

/* Provider Types */
#define PROV_RSA_FULL             1
#define PROV_RSA_SIG              2
#define PROV_DSS                  3
#define PROV_FORTEZZA             4
#define PROV_MS_EXCHANGE          5
#define PROV_SSL                  6
#define PROV_RSA_SCHANNEL         12
#define PROV_DSS_DH               13
#define PROV_EC_ECDSA_SIG         14
#define PROV_EC_ECNRA_SIG         15
#define PROV_EC_ECDSA_FULL        16
#define PROV_EC_ECNRA_FULL        17
#define PROV_DH_SCHANNEL          18
#define PROV_SPYRUS_LYNKS         20
#define PROV_RNG                  21
#define PROV_INTEL_SEC            22
#define PROV_REPLACE_OWF          23
#define PROV_RSA_AES              24

/* FLAGS Section */

/* Provider Parameters */
#define PP_ENUMALGS             1
#define PP_ENUMCONTAINERS       2
#define PP_IMPTYPE              3
#define PP_NAME                 4
#define PP_VERSION              5
#define PP_CONTAINER            6

#define CRYPT_FIRST             1
#define CRYPT_NEXT              2

#define CRYPT_IMPL_HARDWARE     1
#define CRYPT_IMPL_SOFTWARE     2
#define CRYPT_IMPL_MIXED        3
#define CRYPT_IMPL_UNKNOWN      4

/* CryptAcquireContext */
#define CRYPT_VERIFYCONTEXT       0xF0000000
#define CRYPT_NEWKEYSET           0x00000008
#define CRYPT_DELETEKEYSET        0x00000010
#define CRYPT_MACHINE_KEYSET      0x00000020
#define CRYPT_SILENT              0x00000040

/* Crypt{Get|Set}Provider */
#define CRYPT_MACHINE_DEFAULT     0x00000001
#define CRYPT_USER_DEFAULT        0x00000002
#define CRYPT_DELETE_DEFAULT      0x00000004

/* Crypt{Get/Set}ProvParam */
#define PP_CLIENT_HWND          1
#define PP_ENUMALGS             1
#define PP_ENUMCONTAINERS       2
#define PP_IMPTYPE              3
#define PP_NAME                 4
#define PP_VERSION              5
#define PP_CONTAINER            6
#define PP_CHANGE_PASSWORD      7
#define PP_KEYSET_SEC_DESCR     8
#define PP_KEY_TYPE_SUBTYPE     10
#define PP_CONTEXT_INFO         11
#define PP_KEYEXCHANGE_KEYSIZE  12
#define PP_SIGNATURE_KEYSIZE    13
#define PP_KEYEXCHANGE_ALG      14
#define PP_SIGNATURE_ALG        15
#define PP_PROVTYPE             16
#define PP_KEYSTORAGE           17
#define PP_SYM_KEYSIZE          19
#define PP_SESSION_KEYSIZE      20
#define PP_UI_PROMPT            21
#define PP_ENUMALGS_EX          22
#define PP_DELETEKEY            24
#define PP_ENUMMANDROOTS        25
#define PP_ENUMELECTROOTS       26
#define PP_KEYSET_TYPE          27
#define PP_ADMIN_PIN            31
#define PP_KEYEXCHANGE_PIN      32
#define PP_SIGNATURE_PIN        33
#define PP_SIG_KEYSIZE_INC      34
#define PP_KEYX_KEYSIZE_INC     35
#define PP_UNIQUE_CONTAINER     36
#define PP_SGC_INFO             37
#define PP_USE_HARDWARE_RNG     38
#define PP_KEYSPEC              39
#define PP_ENUMEX_SIGNING_PROT  40

/* Crypt{Get/Set}KeyParam */
#define KP_IV                   1
#define KP_SALT                 2
#define KP_PADDING              3
#define KP_MODE                 4
#define KP_MODE_BITS            5
#define KP_PERMISSIONS          6
#define KP_ALGID                7
#define KP_BLOCKLEN             8
#define KP_KEYLEN               9
#define KP_SALT_EX              10
#define KP_P                    11
#define KP_G                    12
#define KP_Q                    13
#define KP_X                    14
#define KP_Y                    15
#define KP_RA                   16
#define KP_RB                   17
#define KP_INFO                 18
#define KP_EFFECTIVE_KEYLEN     19
#define KP_SCHANNEL_ALG         20
#define KP_CLIENT_RANDOM        21
#define KP_SERVER_RANDOM        22
#define KP_RP                   23
#define KP_PRECOMP_MD5          24
#define KP_PRECOMP_SHA          25
#define KP_CERTIFICATE          26
#define KP_CLEAR_KEY            27
#define KP_PUB_EX_LEN           28
#define KP_PUB_EX_VAL           29
#define KP_KEYVAL               30
#define KP_ADMIN_PIN            31
#define KP_KEYEXCHANGE_PIN      32
#define KP_SIGNATURE_PIN        33
#define KP_PREHASH              34

/* CryptSignHash/CryptVerifySignature */
#define CRYPT_NOHASHOID         0x00000001
#define CRYPT_TYPE2_FORMAT      0x00000002
#define CRYPT_X931_FORMAT       0x00000004

/* Crypt{Get,Set}HashParam */
#define HP_ALGID                0x0001
#define HP_HASHVAL              0x0002
#define HP_HASHSIZE             0x0004
#define HP_HMAC_INFO            0x0005
#define HP_TLS1PRF_LABEL        0x0006
#define HP_TLS1PRF_SEED         0x0007

/* Crypt{Get,Set}KeyParam */
#define CRYPT_MODE_CBC          1
#define CRYPT_MODE_ECB          2
#define CRYPT_MODE_OFB          3
#define CRYPT_MODE_CFB          4

#define CRYPT_ENCRYPT           0x0001 
#define CRYPT_DECRYPT           0x0002
#define CRYPT_EXPORT            0x0004
#define CRYPT_READ              0x0008
#define CRYPT_WRITE             0x0010
#define CRYPT_MAC               0x0020

/* Crypt*Key */
#define CRYPT_EXPORTABLE        0x00000001
#define CRYPT_USER_PROTECTED    0x00000002
#define CRYPT_CREATE_SALT       0x00000004
#define CRYPT_UPDATE_KEY        0x00000008
#define CRYPT_NO_SALT           0x00000010
#define CRYPT_PREGEN            0x00000040
#define CRYPT_SERVER            0x00000400
#define CRYPT_ARCHIVABLE        0x00004000

/* CryptExportKey */
#define CRYPT_SSL2_FALLBACK     0x00000002
#define CRYPT_DESTROYKEY        0x00000004
#define CRYPT_OAEP              0x00000040

/* CryptHashSessionKey */
#define CRYPT_LITTLE_ENDIAN     0x00000001

/* Crypt{Protect,Unprotect}Data PROMPTSTRUCT flags */
#define CRYPTPROTECT_PROMPT_ON_PROTECT    0x0001
#define CRYPTPROTECT_PROMPT_ON_UNPROTECT  0x0002
/* Crypt{Protect,Unprotect}Data flags */
#define CRYPTPROTECT_UI_FORBIDDEN       0x0001
#define CRYPTPROTECT_LOCAL_MACHINE      0x0004
#define CRYPTPROTECT_AUDIT              0x0010
#define CRYPTPROTECT_VERIFY_PROTECTION  0x0040

/* Blob Types */
#define SIMPLEBLOB              0x1
#define PUBLICKEYBLOB           0x6
#define PRIVATEKEYBLOB          0x7
#define PLAINTEXTKEYBLOB        0x8
#define OPAQUEKEYBLOB           0x9
#define PUBLICKEYBLOBEX         0xA
#define SYMMETRICWRAPKEYBLOB    0xB

#define CUR_BLOB_VERSION        2

/* cert store provider types */
#define CERT_STORE_PROV_MSG                  ((LPCSTR)1)
#define CERT_STORE_PROV_MEMORY               ((LPCSTR)2)
#define CERT_STORE_PROV_FILE                 ((LPCSTR)3)
#define CERT_STORE_PROV_REG                  ((LPCSTR)4)
#define CERT_STORE_PROV_PKCS7                ((LPCSTR)5)
#define CERT_STORE_PROV_SERIALIZED           ((LPCSTR)6)
#define CERT_STORE_PROV_FILENAME_A           ((LPCSTR)7)
#define CERT_STORE_PROV_FILENAME_W           ((LPCSTR)8)
#define CERT_STORE_PROV_SYSTEM_A             ((LPCSTR)9)
#define CERT_STORE_PROV_SYSTEM_W             ((LPCSTR)10)
#define CERT_STORE_PROV_SYSTEM               CERT_STORE_PROV_SYSTEM_W
#define CERT_STORE_PROV_COLLECTION           ((LPCSTR)11)
#define CERT_STORE_PROV_SYSTEM_REGISTRY_A    ((LPCSTR)12)
#define CERT_STORE_PROV_SYSTEM_REGISTRY_W    ((LPCSTR)13)
#define CERT_STORE_PROV_SYSTEM_REGISTRY      CERT_STORE_PROV_SYSTEM_REGISTRY_W
#define CERT_STORE_PROV_PHYSICAL_W           ((LPCSTR)14)
#define CERT_STORE_PROV_PHYSICAL             CERT_STORE_PROV_PHYSICAL_W
#define CERT_STORE_PROV_SMART_CARD_W         ((LPCSTR)15)
#define CERT_STORE_PROV_SMART_CARD           CERT_STORE_PROV_SMART_CARD_W
#define CERT_STORE_PROV_LDAP_W               ((LPCSTR)16)
#define CERT_STORE_PROV_LDAP                 CERT_STORE_PROV_LDAP_W

#define sz_CERT_STORE_PROV_MEMORY            "Memory"
#define sz_CERT_STORE_PROV_FILENAME_W        "File"
#define sz_CERT_STORE_PROV_FILENAME          sz_CERT_STORE_PROV_FILENAME_W
#define sz_CERT_STORE_PROV_SYSTEM_W          "System"
#define sz_CERT_STORE_PROV_SYSTEM            sz_CERT_STORE_PROV_SYSTEM_W
#define sz_CERT_STORE_PROV_PKCS7             "PKCS7"
#define sz_CERT_STORE_PROV_SERIALIZED        "Serialized"
#define sz_CERT_STORE_PROV_COLLECTION        "Collection"
#define sz_CERT_STORE_PROV_SYSTEM_REGISTRY_W "SystemRegistry"
#define sz_CERT_STORE_PROV_SYSTEM_REGISTRY   sz_CERT_STORE_PROV_SYSTEM_REGISTRY_W
#define sz_CERT_STORE_PROV_PHYSICAL_W        "Physical"
#define sz_CERT_STORE_PROV_PHYSICAL          sz_CERT_STORE_PROV_PHYSICAL_W
#define sz_CERT_STORE_PROV_SMART_CARD_W      "SmartCard"
#define sz_CERT_STORE_PROV_SMART_CARD        sz_CERT_STORE_PROV_SMART_CARD_W
#define sz_CERT_STORE_PROV_LDAP_W            "Ldap"
#define sz_CERT_STORE_PROV_LDAP              sz_CERT_STORE_PROV_LDAP_W

/* types for CertOpenStore dwEncodingType */
#define CERT_ENCODING_TYPE_MASK 0x0000ffff
#define CMSG_ENCODING_TYPE_MASK 0xffff0000
#define GET_CERT_ENCODING_TYPE(x) ((x) & CERT_ENCODING_TYPE_MASK)
#define GET_CMSG_ENCODING_TYPE(x) ((x) & CMSG_ENCODING_TYPE_MASK)

#define CRYPT_ASN_ENCODING  0x00000001
#define CRYPT_NDR_ENCODING  0x00000002
#define X509_ASN_ENCODING   0x00000001
#define X509_NDR_ENCODING   0x00000002
#define PKCS_7_ASN_ENCODING 0x00010000
#define PKCS_7_NDR_ENCODING 0x00020000

/* system store locations */
#define CERT_SYSTEM_STORE_LOCATION_MASK  0x00ff0000
#define CERT_SYSTEM_STORE_LOCATION_SHIFT 16

/* system store location ids */
/* hkcu */
#define CERT_SYSTEM_STORE_CURRENT_USER_ID               1
/* hklm */
#define CERT_SYSTEM_STORE_LOCAL_MACHINE_ID              2
/* hklm\Software\Microsoft\Cryptography\Services */
#define CERT_SYSTEM_STORE_CURRENT_SERVICE_ID            4
#define CERT_SYSTEM_STORE_SERVICES_ID                   5
/* HKEY_USERS */
#define CERT_SYSTEM_STORE_USERS_ID                      6
/* hkcu\Software\Microsoft\Policies\Microsoft\SystemCertificates */
#define CERT_SYSTEM_STORE_CURRENT_USER_GROUP_POLICY_ID  7
/* hklm\Software\Microsoft\Policies\Microsoft\SystemCertificates */
#define CERT_SYSTEM_STORE_LOCAL_MACHINE_GROUP_POLICY_ID 8
/* hklm\Software\Microsoft\EnterpriseCertificates */
#define CERT_SYSTEM_STORE_LOCAL_MACHINE_ENTERPRISE_ID   9

/* system store location values */
#define CERT_SYSTEM_STORE_CURRENT_USER \
 (CERT_SYSTEM_STORE_CURRENT_USER_ID << CERT_SYSTEM_STORE_LOCATION_SHIFT)
#define CERT_SYSTEM_STORE_LOCAL_MACHINE \
 (CERT_SYSTEM_STORE_LOCAL_MACHINE_ID << CERT_SYSTEM_STORE_LOCATION_SHIFT)
#define CERT_SYSTEM_STORE_CURRENT_SERVICE \
 (CERT_SYSTEM_STORE_CURRENT_SERVICE_ID << CERT_SYSTEM_STORE_LOCATION_SHIFT)
#define CERT_SYSTEM_STORE_SERVICE \
 (CERT_SYSTEM_STORE_SERVICES_ID << CERT_SYSTEM_STORE_LOCATION_SHIFT)
#define CERT_SYSTEM_STORE_USERS \
 (CERT_SYSTEM_STORE_USERS_ID << CERT_SYSTEM_STORE_LOCATION_SHIFT)
#define CERT_SYSTEM_STORE_CURRENT_USER_GROUP_POLICY \
 (CERT_SYSTEM_STORE_CURRENT_USER_GROUP_POLICY_ID << CERT_SYSTEM_STORE_LOCATION_SHIFT)
#define CERT_SYSTEM_STORE_LOCAL_MACHINE_GROUP_POLICY \
 (CERT_SYSTEM_STORE_LOCAL_MACHINE_GROUP_POLICY_ID << CERT_SYSTEM_STORE_LOCATION_SHIFT)
#define CERT_SYSTEM_STORE_LOCAL_MACHINE_ENTERPRISE \
 (CERT_SYSTEM_STORE_LOCAL_MACHINE_ENTERPRISE_ID << CERT_SYSTEM_STORE_LOCATION_SHIFT)

/* flags for CertOpenStore dwFlags */
#define CERT_STORE_NO_CRYPT_RELEASE_FLAG            0x00000001
#define CERT_STORE_SET_LOCALIZED_NAME_FLAG          0x00000002
#define CERT_STORE_DEFER_CLOSE_UNTIL_LAST_FREE_FLAG 0x00000004
#define CERT_STORE_DELETE_FLAG                      0x00000010
#define CERT_STORE_UNSAFE_PHYSICAL_FLAG             0x00000020
#define CERT_STORE_SHARE_STORE_FLAG                 0x00000040
#define CERT_STORE_SHARE_CONTEXT_FLAG               0x00000080
#define CERT_STORE_MANIFOLD_FLAG                    0x00000100
#define CERT_STORE_ENUM_ARCHIVED_FLAG               0x00000200
#define CERT_STORE_UPDATE_KEYID_FLAG                0x00000400
#define CERT_STORE_BACKUP_RESTORE_FLAG              0x00000800
#define CERT_STORE_MAXIMUM_ALLOWED_FLAG             0x00001000
#define CERT_STORE_CREATE_NEW_FLAG                  0x00002000
#define CERT_STORE_OPEN_EXISTING_FLAG               0x00004000
#define CERT_STORE_READONLY_FLAG                    0x00008000

/* physical store dwFlags, also used by CertAddStoreToCollection as
 * dwUpdateFlags
 */
#define CERT_PHYSICAL_STORE_ADD_ENABLE_FLAG                  0x1
#define CERT_PHYSICAL_STORE_OPEN_DISABLE_FLAG                0x2
#define CERT_PHYSICAL_STORE_REMOVE_OPEN_DISABLE_FLAG         0x4
#define CERT_PHYSICAL_STORE_INSERT_COMPUTER_NAME_ENABLE_FLAG 0x8

/* dwFlag values for CertEnumPhysicalStore callback */
#define CERT_PHYSICAL_STORE_PREDEFINED_ENUM_FLAG 0x1

/* predefined store names */
#if defined(__GNUC__)
# define CERT_PHYSICAL_STORE_DEFAULT_NAME (const WCHAR[])\
 {'.','D','e','f','a','u','l','t','0'}
# define CERT_PHYSICAL_STORE_GROUP_POLICY_NAME (const WCHAR[])\
 {'.','G','r','o','u','p','P','o','l','i','c','y',0}
# define CERT_PHYSICAL_STORE_LOCAL_MACHINE_NAME (const WCHAR[])\
 {'.','L','o','c','a','l','M','a','c','h','i','n','e',0}
# define CERT_PHYSICAL_STORE_DS_USER_CERTIFICATE_NAME (const WCHAR[])\
 {'.','U','s','e','r','C','e','r','t','i','f','i','c','a','t','e',0}
# define CERT_PHYSICAL_STORE_LOCAL_MACHINE_GROUP_POLICY_NAME (const WCHAR[])\
 {'.','L','o','c','a','l','M','a','c','h','i','n','e','G','r','o','u','p',\
 'P','o','l','i','c','y',0}
# define CERT_PHYSICAL_STORE_ENTERPRISE_NAME (const WCHAR[])\
 {'.','E','n','t','e','r','p','r','i','s','e',0}
# define CERT_PHYSICAL_STORE_AUTH_ROOT_NAME (const WCHAR[])\
 {'.','A','u','t','h','R','o','o','t',0}
#elif defined(_MSC_VER)
# define CERT_PHYSICAL_STORE_DEFAULT_NAME \
 L".Default"
# define CERT_PHYSICAL_STORE_GROUP_POLICY_NAME \
 L".GroupPolicy"
# define CERT_PHYSICAL_STORE_LOCAL_MACHINE_NAME \
 L".LocalMachine"
# define CERT_PHYSICAL_STORE_DS_USER_CERTIFICATE_NAME \
 L".UserCertificate"
# define CERT_PHYSICAL_STORE_LOCAL_MACHINE_GROUP_POLICY_NAME \
 L".LocalMachineGroupPolicy"
# define CERT_PHYSICAL_STORE_ENTERPRISE_NAME \
 L".Enterprise"
# define CERT_PHYSICAL_STORE_AUTH_ROOT_NAME \
 L".AuthRoot"
#else
static const WCHAR CERT_PHYSICAL_STORE_DEFAULT_NAME[] = 
 {'.','D','e','f','a','u','l','t','0'};
static const WCHAR CERT_PHYSICAL_STORE_GROUP_POLICY_NAME[] =
 {'.','G','r','o','u','p','P','o','l','i','c','y',0};
static const WCHAR CERT_PHYSICAL_STORE_LOCAL_MACHINE_NAME[] =
 {'.','L','o','c','a','l','M','a','c','h','i','n','e',0};
static const WCHAR CERT_PHYSICAL_STORE_DS_USER_CERTIFICATE_NAME[] =
 {'.','U','s','e','r','C','e','r','t','i','f','i','c','a','t','e',0};
static const WCHAR CERT_PHYSICAL_STORE_LOCAL_MACHINE_GROUP_POLICY_NAME[] =
 {'.','L','o','c','a','l','M','a','c','h','i','n','e','G','r','o','u','p',
 'P','o','l','i','c','y',0};
static const WCHAR CERT_PHYSICAL_STORE_ENTERPRISE_NAME[] =
 {'.','E','n','t','e','r','p','r','i','s','e',0};
static const WCHAR CERT_PHYSICAL_STORE_AUTH_ROOT_NAME[] =
 {'.','A','u','t','h','R','o','o','t',0};
#endif

/* cert system store flags */
#define CERT_SYSTEM_STORE_MASK 0xffff0000
#define CERT_SYSTEM_STORE_RELOCATE_FLAG 0x80000000

/* CertFindChainInStore dwFindType types */
#define CERT_CHAIN_FIND_BY_ISSUER 1

/* CERT_RDN attribute dwValueType types */
#define CERT_RDN_TYPE_MASK 0x000000ff
#define CERT_RDN_ANY_TYPE         0
#define CERT_RDN_ENCODED_BLOB     1
#define CERT_RDN_OCTET_STRING     2
#define CERT_RDN_NUMERIC_STRING   3
#define CERT_RDN_PRINTABLE_STRING 4
#define CERT_RDN_TELETEX_STRING   5
#define CERT_RDN_T61_STRING       5
#define CERT_RDN_VIDEOTEX_STRING  6
#define CERT_RDN_IA5_STRING       7
#define CERT_RDN_GRAPHIC_STRING   8
#define CERT_RDN_VISIBLE_STRING   9
#define CERT_RDN_ISO646_STRING    9
#define CERT_RDN_GENERAL_STRING   10
#define CERT_RDN_UNIVERSAL_STRING 11
#define CERT_RDN_INT4_STRING      11
#define CERT_RDN_BMP_STRING       12
#define CERT_RDN_UNICODE_STRING   12
#define CERT_RDN_UTF8_STRING      13

/* CERT_RDN attribute dwValueType flags */
#define CERT_RDN_FLAGS_MASK 0xff000000
#define CERT_RDN_ENABLE_T61_UNICODE_FLAG  0x80000000
#define CERT_RDN_DISABLE_CHECK_TYPE_FLAG  0x4000000
#define CERT_RDN_ENABLE_UTF8_UNICODE_FLAG 0x2000000
#define CERT_RDN_DISABLE_IE4_UTF8_FLAG    0x0100000

#define IS_CERT_RDN_CHAR_STRING(x) \
 (((x) & CERT_RDN_TYPE_MASK) >= CERT_RDN_NUMERIC_STRING)

/* OIDs */
#define szOID_RSA                           "1.2.840.113549"
#define szOID_PKCS                          "1.2.840.113549.1"
#define szOID_RSA_HASH                      "1.2.840.113549.2"
#define szOID_RSA_ENCRYPT                   "1.2.840.113549.3"
#define szOID_PKCS_1                        "1.2.840.113549.1.1"
#define szOID_PKCS_2                        "1.2.840.113549.1.2"
#define szOID_PKCS_3                        "1.2.840.113549.1.3"
#define szOID_PKCS_4                        "1.2.840.113549.1.4"
#define szOID_PKCS_5                        "1.2.840.113549.1.5"
#define szOID_PKCS_6                        "1.2.840.113549.1.6"
#define szOID_PKCS_7                        "1.2.840.113549.1.7"
#define szOID_PKCS_8                        "1.2.840.113549.1.8"
#define szOID_PKCS_9                        "1.2.840.113549.1.9"
#define szOID_PKCS_10                       "1.2.840.113549.1.10"
#define szOID_PKCS_11                       "1.2.840.113549.1.12"
#define szOID_RSA_RSA                       "1.2.840.113549.1.1.1"
#define CERT_RSA_PUBLIC_KEY_OBJID           szOID_RSA_RSA
#define CERT_DEFAULT_OID_PUBLIC_KEY_SIGN    szOID_RSA_RSA
#define CERT_DEFAULT_OID_PUBLIC_KEY_XCHG    szOID_RSA_RSA
#define szOID_RSA_MD2RSA                    "1.2.840.113549.1.1.2"
#define szOID_RSA_MD4RSA                    "1.2.840.113549.1.1.3"
#define szOID_RSA_MD5RSA                    "1.2.840.113549.1.1.4"
#define szOID_RSA_SHA1RSA                   "1.2.840.113549.1.1.5"
#define szOID_RSA_SET0AEP_RSA               "1.2.840.113549.1.1.6"
#define szOID_RSA_DH                        "1.2.840.113549.1.3.1"
#define szOID_RSA_data                      "1.2.840.113549.1.7.1"
#define szOID_RSA_signedData                "1.2.840.113549.1.7.2"
#define szOID_RSA_envelopedData             "1.2.840.113549.1.7.3"
#define szOID_RSA_signEnvData               "1.2.840.113549.1.7.4"
#define szOID_RSA_digestedData              "1.2.840.113549.1.7.5"
#define szOID_RSA_hashedData                "1.2.840.113549.1.7.5"
#define szOID_RSA_encryptedData             "1.2.840.113549.1.7.6"
#define szOID_RSA_emailAddr                 "1.2.840.113549.1.9.1"
#define szOID_RSA_unstructName              "1.2.840.113549.1.9.2"
#define szOID_RSA_contentType               "1.2.840.113549.1.9.3"
#define szOID_RSA_messageDigest             "1.2.840.113549.1.9.4"
#define szOID_RSA_signingTime               "1.2.840.113549.1.9.5"
#define szOID_RSA_counterSign               "1.2.840.113549.1.9.6"
#define szOID_RSA_challengePwd              "1.2.840.113549.1.9.7"
#define szOID_RSA_unstructAddr              "1.2.840.113549.1.9.9"
#define szOID_RSA_extCertAttrs              "1.2.840.113549.1.9.9"
#define szOID_RSA_certExtensions            "1.2.840.113549.1.9.14"
#define szOID_RSA_SMIMECapabilities         "1.2.840.113549.1.9.15"
#define szOID_RSA_preferSignedData          "1.2.840.113549.1.9.15.1"
#define szOID_RSA_SMIMEalg                  "1.2.840.113549.1.9.16.3"
#define szOID_RSA_SMIMEalgESDH              "1.2.840.113549.1.9.16.3.5"
#define szOID_RSA_SMIMEalgCMS3DESwrap       "1.2.840.113549.1.9.16.3.6"
#define szOID_RSA_SMIMEalgCMSRC2wrap        "1.2.840.113549.1.9.16.3.7"
#define szOID_RSA_MD2                       "1.2.840.113549.2.2"
#define szOID_RSA_MD4                       "1.2.840.113549.2.4"
#define szOID_RSA_RC2CBC                    "1.2.840.113549.3.2"
#define szOID_RSA_RC4                       "1.2.840.113549.3.4"
#define szOID_RSA_DES_EDE3_CBC              "1.2.840.113549.3.7"
#define szOID_RSA_RC5_CBCPad                "1.2.840.113549.3.9"
#define szOID_ANSI_X942                     "1.2.840.10046"
#define szOID_ANSI_X942_DH                  "1.2.840.10046.2.1"
#define szOID_ANSI_X957                     "1.2.840.10040"
#define szOID_ANSI_X957_DSA                 "1.2.840.10040.4.1"
#define szOID_ANSI_X957_SHA1DSA             "1.2.840.10040.4.3"
#define szOID_DS                            "2.5"
#define szOID_DSALG                         "2.5.8"
#define szOID_DSALG_CRPT                    "2.5.8.1"
#define szOID_DSALG_HASH                    "2.5.8.2"
#define szOID_DSALG_SIGN                    "2.5.8.3"
#define szOID_DSALG_RSA                     "2.5.8.1.1"
#define szOID_OIW                           "1.3.14"
#define szOID_OIWSEC                        "1.3.14.3.2"
#define szOID_OIWSEC_md4RSA                 "1.3.14.3.2.2.2"
#define szOID_OIWSEC_md5RSA                 "1.3.14.3.2.2.3"
#define szOID_OIWSEC_md4RSA2                "1.3.14.3.2.2.4"
#define szOID_OIWSEC_desECB                 "1.3.14.3.2.2.6"
#define szOID_OIWSEC_desCBC                 "1.3.14.3.2.2.7"
#define szOID_OIWSEC_desOFB                 "1.3.14.3.2.2.8"
#define szOID_OIWSEC_desCFB                 "1.3.14.3.2.2.9"
#define szOID_OIWSEC_desMAC                 "1.3.14.3.2.2.10"
#define szOID_OIWSEC_rsaSign                "1.3.14.3.2.2.11"
#define szOID_OIWSEC_dsa                    "1.3.14.3.2.2.12"
#define szOID_OIWSEC_shaDSA                 "1.3.14.3.2.2.13"
#define szOID_OIWSEC_mdc2RSA                "1.3.14.3.2.2.14"
#define szOID_OIWSEC_shaRSA                 "1.3.14.3.2.2.15"
#define szOID_OIWSEC_dhCommMod              "1.3.14.3.2.2.16"
#define szOID_OIWSEC_desEDE                 "1.3.14.3.2.2.17"
#define szOID_OIWSEC_sha                    "1.3.14.3.2.2.18"
#define szOID_OIWSEC_mdc2                   "1.3.14.3.2.2.19"
#define szOID_OIWSEC_dsaComm                "1.3.14.3.2.2.20"
#define szOID_OIWSEC_dsaCommSHA             "1.3.14.3.2.2.21"
#define szOID_OIWSEC_rsaXchg                "1.3.14.3.2.2.22"
#define szOID_OIWSEC_keyHashSeal            "1.3.14.3.2.2.23"
#define szOID_OIWSEC_md2RSASign             "1.3.14.3.2.2.24"
#define szOID_OIWSEC_md5RSASign             "1.3.14.3.2.2.25"
#define szOID_OIWSEC_sha1                   "1.3.14.3.2.2.26"
#define szOID_OIWSEC_dsaSHA1                "1.3.14.3.2.2.27"
#define szOID_OIWSEC_dsaCommSHA1            "1.3.14.3.2.2.28"
#define szOID_OIWSEC_sha1RSASign            "1.3.14.3.2.2.29"
#define szOID_OIWDIR                        "1.3.14.7.2"
#define szOID_OIWDIR_CRPT                   "1.3.14.7.2.1"
#define szOID_OIWDIR_HASH                   "1.3.14.7.2.2"
#define szOID_OIWDIR_SIGN                   "1.3.14.7.2.3"
#define szOID_OIWDIR_md2                    "1.3.14.7.2.2.1"
#define szOID_OIWDIR_md2RSA                 "1.3.14.7.2.3.1"
#define szOID_INFOSEC                       "2.16.840.1.101.2.1"
#define szOID_INFOSEC_sdnsSignature         "2.16.840.1.101.2.1.1.1"
#define szOID_INFOSEC_mosaicSignature       "2.16.840.1.101.2.1.1.2"
#define szOID_INFOSEC_sdnsConfidentiality   "2.16.840.1.101.2.1.1.3"
#define szOID_INFOSEC_mosaicConfidentiality "2.16.840.1.101.2.1.1.4"
#define szOID_INFOSEC_sdnsIntegrity         "2.16.840.1.101.2.1.1.5"
#define szOID_INFOSEC_mosaicIntegrity       "2.16.840.1.101.2.1.1.6"
#define szOID_INFOSEC_sdnsTokenProtection   "2.16.840.1.101.2.1.1.7"
#define szOID_INFOSEC_mosaicTokenProtection "2.16.840.1.101.2.1.1.8"
#define szOID_INFOSEC_sdnsKeyManagement     "2.16.840.1.101.2.1.1.9"
#define szOID_INFOSEC_mosaicKeyManagement   "2.16.840.1.101.2.1.1.10"
#define szOID_INFOSEC_sdnsKMandSig          "2.16.840.1.101.2.1.1.11"
#define szOID_INFOSEC_mosaicKMandSig        "2.16.840.1.101.2.1.1.12"
#define szOID_INFOSEC_SuiteASignature       "2.16.840.1.101.2.1.1.13"
#define szOID_INFOSEC_SuiteAConfidentiality "2.16.840.1.101.2.1.1.14"
#define szOID_INFOSEC_SuiteAIntegrity       "2.16.840.1.101.2.1.1.15"
#define szOID_INFOSEC_SuiteATokenProtection "2.16.840.1.101.2.1.1.16"
#define szOID_INFOSEC_SuiteAKeyManagement   "2.16.840.1.101.2.1.1.17"
#define szOID_INFOSEC_SuiteAKMandSig        "2.16.840.1.101.2.1.1.18"
#define szOID_INFOSEC_mosaicUpdatedSig      "2.16.840.1.101.2.1.1.19"
#define szOID_INFOSEC_mosaicKMandUpdSig     "2.16.840.1.101.2.1.1.20"
#define szOID_INFOSEC_mosaicUpdateInteg     "2.16.840.1.101.2.1.1.21"
#define szOID_COMMON_NAME                   "2.5.4.3"
#define szOID_SUR_NAME                      "2.5.4.4"
#define szOID_DEVICE_SERIAL_NUMBER          "2.5.4.5"
#define szOID_COUNTRY_NAME                  "2.5.4.6"
#define szOID_LOCALITY_NAME                 "2.5.4.7"
#define szOID_STATE_OR_PROVINCE_NAME        "2.5.4.8"
#define szOID_STREET_ADDRESS                "2.5.4.9"
#define szOID_ORGANIZATION_NAME             "2.5.4.10"
#define szOID_ORGANIZATIONAL_UNIT_NAME      "2.5.4.11"
#define szOID_TITLE                         "2.5.4.12"
#define szOID_DESCRIPTION                   "2.5.4.13"
#define szOID_SEARCH_GUIDE                  "2.5.4.14"
#define szOID_BUSINESS_CATEGORY             "2.5.4.15"
#define szOID_POSTAL_ADDRESS                "2.5.4.16"
#define szOID_POSTAL_CODE                   "2.5.4.17"
#define szOID_POST_OFFICE_BOX               "2.5.4.18"
#define szOID_PHYSICAL_DELIVERY_OFFICE_NAME "2.5.4.19"
#define szOID_TELEPHONE_NUMBER              "2.5.4.20"
#define szOID_TELEX_NUMBER                  "2.5.4.21"
#define szOID_TELETEXT_TERMINAL_IDENTIFIER  "2.5.4.22"
#define szOID_FACSIMILE_TELEPHONE_NUMBER    "2.5.4.23"
#define szOID_X21_ADDRESS                   "2.5.4.24"
#define szOID_INTERNATIONAL_ISDN_NUMBER     "2.5.4.25"
#define szOID_REGISTERED_ADDRESS            "2.5.4.26"
#define szOID_DESTINATION_INDICATOR         "2.5.4.27"
#define szOID_PREFERRED_DELIVERY_METHOD     "2.5.4.28"
#define szOID_PRESENTATION_ADDRESS          "2.5.4.29"
#define szOID_SUPPORTED_APPLICATION_CONTEXT "2.5.4.30"
#define szOID_MEMBER                        "2.5.4.31"
#define szOID_OWNER                         "2.5.4.32"
#define szOID_ROLE_OCCUPANT                 "2.5.4.33"
#define szOID_SEE_ALSO                      "2.5.4.34"
#define szOID_USER_PASSWORD                 "2.5.4.35"
#define szOID_USER_CERTIFICATE              "2.5.4.36"
#define szOID_CA_CERTIFICATE                "2.5.4.37"
#define szOID_AUTHORITY_REVOCATION_LIST     "2.5.4.38"
#define szOID_CERTIFICATE_REVOCATION_LIST   "2.5.4.39"
#define szOID_CROSS_CERTIFICATE_PAIR        "2.5.4.40"
#define szOID_GIVEN_NAME                    "2.5.4.42"
#define szOID_INITIALS                      "2.5.4.43"
#define szOID_DN_QUALIFIER                  "2.5.4.46"
#define szOID_DOMAIN_COMPONENT              "0.9.2342.19200300.100.1.25"
#define szOID_PKCS_12_FRIENDLY_NAME_ATTR     "1.2.840.113549.1.9.20"
#define szOID_PKCS_12_LOCAL_KEY_ID           "1.2.840.113549.1.9.21"
#define szOID_PKCS_12_KEY_PROVIDER_NAME_ATTR "1.3.6.1.4.1.311.17.1"
#define szOID_LOCAL_MACHINE_KEYSET           "1.3.6.1.4.1.311.17.2"
#define szOID_KEYID_RDN                      "1.3.6.1.4.1.311.10.7.1"
#define CRYPT_ENCODE_DECODE_NONE             0
#define X509_CERT                            ((LPCSTR)1)
#define X509_CERT_TO_BE_SIGNED               ((LPCSTR)2)
#define X509_CERT_CRL_TO_BE_SIGNED           ((LPCSTR)3)
#define X509_CERT_REQUEST_TO_BE_SIGNED       ((LPCSTR)4)
#define X509_EXTENSIONS                      ((LPCSTR)5)
#define X509_NAME_VALUE                      ((LPCSTR)6)
#define X509_ANY_STRING                      X509_NAME_VALUE
#define X509_NAME                            ((LPCSTR)7)
#define X509_PUBLIC_KEY_INFO                 ((LPCSTR)8)
#define X509_AUTHORITY_KEY_ID                ((LPCSTR)9)
#define X509_KEY_ATTRIBUTES                  ((LPCSTR)10)
#define X509_KEY_USAGE_RESTRICTION           ((LPCSTR)11)
#define X509_ALTERNATE_NAME                  ((LPCSTR)12)
#define X509_BASIC_CONSTRAINTS               ((LPCSTR)13)
#define X509_KEY_USAGE                       ((LPCSTR)14)
#define X509_BASIC_CONSTRAINTS2              ((LPCSTR)15)
#define X509_CERT_POLICIES                   ((LPCSTR)16)
#define PKCS_UTC_TIME                        ((LPCSTR)17)
#define PKCS_TIME_REQUEST                    ((LPCSTR)18)
#define RSA_CSP_PUBLICKEYBLOB                ((LPCSTR)19)
#define X509_UNICODE_NAME                    ((LPCSTR)20)
#define X509_KEYGEN_REQUEST_TO_BE_SIGNED     ((LPCSTR)21)
#define PKCS_ATTRIBUTE                       ((LPCSTR)22)
#define PKCS_CONTENT_INFO_SEQUENCE_OF_ANY    ((LPCSTR)23)
#define X509_UNICODE_NAME_VALUE              ((LPCSTR)24)
#define X509_UNICODE_ANY_STRING              X509_UNICODE_NAME_VALUE
#define X509_OCTET_STRING                    ((LPCSTR)25)
#define X509_BITS                            ((LPCSTR)26)
#define X509_INTEGER                         ((LPCSTR)27)
#define X509_MULTI_BYTE_INTEGER              ((LPCSTR)28)
#define X509_ENUMERATED                      ((LPCSTR)29)
#define X509_CRL_REASON_CODE                 X509_ENUMERATED
#define X509_CHOICE_OF_TIME                  ((LPCSTR)30)
#define X509_AUTHORITY_KEY_ID2               ((LPCSTR)31)
#define X509_AUTHORITY_INFO_ACCESS           ((LPCSTR)32)
#define PKCS_CONTENT_INFO                    ((LPCSTR)33)
#define X509_SEQUENCE_OF_ANY                 ((LPCSTR)34)
#define X509_CRL_DIST_POINTS                 ((LPCSTR)35)
#define X509_ENHANCED_KEY_USAGE              ((LPCSTR)36)
#define PKCS_CTL                             ((LPCSTR)37)
#define X509_MULTI_BYTE_UINT                 ((LPCSTR)38)
#define X509_DSS_PUBLICKEY                   X509_MULTI_BYTE_UINT
#define X509_DSS_PARAMETERS                  ((LPCSTR)39)
#define X509_DSS_SIGNATURE                   ((LPCSTR)40)
#define PKCS_RC2_CBC_PARAMETERS              ((LPCSTR)41)
#define PKCS_SMIME_CAPABILITIES              ((LPCSTR)42)
#define PKCS_RSA_PRIVATE_KEY                 ((LPCSTR)43)
#define PKCS_PRIVATE_KEY_INFO                ((LPCSTR)44)
#define PKCS_ENCRYPTED_PRIVATE_KEY_INFO      ((LPCSTR)45)
#define X509_PKIX_POLICY_QUALIFIER_USERNOTICE ((LPCSTR)46)
#define X509_DH_PUBLICKEY                    X509_MULTI_BYTE_UINT
#define X509_DH_PARAMETERS                   ((LPCSTR)47)
#define PKCS_ATTRIBUTES                      ((LPCSTR)48)
#define PKCS_SORTED_CTL                      ((LPCSTR)49)
#define X942_DH_PARAMETERS                   ((LPCSTR)50)
#define X509_BITS_WITHOUT_TRAILING_ZEROES    ((LPCSTR)51)
#define X942_OTHER_INFO                      ((LPCSTR)52)
#define X509_CERT_PAIR                       ((LPCSTR)53)
#define X509_ISSUING_DIST_POINT              ((LPCSTR)54)
#define X509_NAME_CONSTRAINTS                ((LPCSTR)55)
#define X509_POLICY_MAPPINGS                 ((LPCSTR)56)
#define X509_POLICY_CONSTRAINTS              ((LPCSTR)57)
#define X509_CROSS_CERT_DIST_POINTS          ((LPCSTR)58)
#define CMC_DATA                             ((LPCSTR)59)
#define CMC_RESPONSE                         ((LPCSTR)60)
#define CMC_STATUS                           ((LPCSTR)61)
#define CMC_ADD_EXTENSIONS                   ((LPCSTR)62)
#define CMC_ADD_ATTRIBUTES                   ((LPCSTR)63)
#define X509_CERTIFICATE_TEMPLATE            ((LPCSTR)64)
#define PKCS7_SIGNER_INFO                    ((LPCSTR)500)
#define CMS_SIGNER_INFO                      ((LPCSTR)501)

/* encode/decode flags */
#define CRYPT_ENCODE_NO_SIGNATURE_BYTE_REVERSAL_FLAG           0x00008
#define CRYPT_ENCODE_ALLOC_FLAG                                0x08000
#define CRYPT_SORTED_CTL_ENCODE_HASHED_SUBJECT_IDENTIFIER_FLAG 0x10000
#define CRYPT_UNICODE_NAME_ENCODE_ENABLE_T61_UNICODE_FLAG \
 CERT_RDN_ENABLE_T61_UNICODE_FLAG
#define CRYPT_UNICODE_NAME_ENCODE_ENABLE_UTF8_UNICODE_FLAG \
 CERT_RDN_ENABLE_UTF8_UNICODE_FLAG
#define CRYPT_UNICODE_NAME_ENCODE_DISABLE_CHECK_TYPE_FLAG \
 CERT_RDN_DISABLE_CHECK_TYPE_FLAG

#define CRYPT_DECODE_NOCOPY_FLAG                               0x00001
#define CRYPT_DECODE_TO_BE_SIGNED_FLAG                         0x00002
#define CRYPT_DECODE_SHARE_OID_STRING_FLAG                     0x00004
#define CRYPT_DECODE_NO_SIGNATURE_BYTE_REVERSAL_FLAG           0x00008
#define CRYPT_DECODE_ALLOC_FLAG                                0x08000
#define CRYPT_UNICODE_NAME_DECODE_DISABLE_IE4_UTF8_FLAG \
 CERT_RDN_DISABLE_IE4_UTF8_FLAG

/* function declarations */
/* advapi32.dll */
BOOL WINAPI CryptAcquireContextA(HCRYPTPROV *phProv, LPCSTR pszContainer,
				   LPCSTR pszProvider, DWORD dwProvType,
				   DWORD dwFlags);
BOOL WINAPI CryptAcquireContextW (HCRYPTPROV *phProv, LPCWSTR pszContainer,
		LPCWSTR pszProvider, DWORD dwProvType, DWORD dwFlags);
#define CryptAcquireContext WINELIB_NAME_AW(CryptAcquireContext)
BOOL WINAPI CryptGenRandom (HCRYPTPROV hProv, DWORD dwLen, BYTE *pbBuffer);
BOOL WINAPI CryptContextAddRef (HCRYPTPROV hProv, DWORD *pdwReserved, DWORD dwFlags);
BOOL WINAPI CryptCreateHash (HCRYPTPROV hProv, ALG_ID Algid, HCRYPTKEY hKey,
		DWORD dwFlags, HCRYPTHASH *phHash);
BOOL WINAPI CryptDecrypt (HCRYPTKEY hKey, HCRYPTHASH hHash, BOOL Final,
		DWORD dwFlags, BYTE *pbData, DWORD *pdwDataLen);
BOOL WINAPI CryptDeriveKey (HCRYPTPROV hProv, ALG_ID Algid, HCRYPTHASH hBaseData,
		DWORD dwFlags, HCRYPTKEY *phKey);
BOOL WINAPI CryptDestroyHash (HCRYPTHASH hHash);
BOOL WINAPI CryptDestroyKey (HCRYPTKEY hKey);
BOOL WINAPI CryptDuplicateKey (HCRYPTKEY hKey, DWORD *pdwReserved, DWORD dwFlags, HCRYPTKEY *phKey);
BOOL WINAPI CryptDuplicateHash (HCRYPTHASH hHash, DWORD *pdwReserved,
		DWORD dwFlags, HCRYPTHASH *phHash);
BOOL WINAPI CryptEncrypt (HCRYPTKEY hKey, HCRYPTHASH hHash, BOOL Final,
		DWORD dwFlags, BYTE *pbData, DWORD *pdwDataLen, DWORD dwBufLen);
BOOL WINAPI CryptEnumProvidersA (DWORD dwIndex, DWORD *pdwReserved,
		DWORD dwFlags, DWORD *pdwProvType, LPSTR pszProvName, DWORD *pcbProvName);
BOOL WINAPI CryptEnumProvidersW (DWORD dwIndex, DWORD *pdwReserved,
		DWORD dwFlags, DWORD *pdwProvType, LPWSTR pszProvName, DWORD *pcbProvName);
#define CryptEnumProviders WINELIB_NAME_AW(CryptEnumProviders)
BOOL WINAPI CryptEnumProviderTypesA (DWORD dwIndex, DWORD *pdwReserved,
		DWORD dwFlags, DWORD *pdwProvType, LPSTR pszTypeName, DWORD *pcbTypeName);
BOOL WINAPI CryptEnumProviderTypesW (DWORD dwIndex, DWORD *pdwReserved,
		DWORD dwFlags, DWORD *pdwProvType, LPWSTR pszTypeName, DWORD *pcbTypeName);
#define CryptEnumProviderTypes WINELIB_NAME_AW(CryptEnumProviderTypes)
BOOL WINAPI CryptExportKey (HCRYPTKEY hKey, HCRYPTKEY hExpKey, DWORD dwBlobType,
		DWORD dwFlags, BYTE *pbData, DWORD *pdwDataLen);
BOOL WINAPI CryptGenKey (HCRYPTPROV hProv, ALG_ID Algid, DWORD dwFlags, HCRYPTKEY *phKey);
BOOL WINAPI CryptGetKeyParam (HCRYPTKEY hKey, DWORD dwParam, BYTE *pbData,
		DWORD *pdwDataLen, DWORD dwFlags);
BOOL WINAPI CryptGetHashParam (HCRYPTHASH hHash, DWORD dwParam, BYTE *pbData,
		DWORD *pdwDataLen, DWORD dwFlags);
BOOL WINAPI CryptGetOIDFunctionValue(DWORD dwEncodingType, LPCSTR pszFuncName,
                                     LPCSTR pszOID, LPCWSTR szValueName, DWORD *pdwValueType,
                                     BYTE *pbValueData, DWORD *pcbValueData);
BOOL WINAPI CryptGetProvParam (HCRYPTPROV hProv, DWORD dwParam, BYTE *pbData,
		DWORD *pdwDataLen, DWORD dwFlags);
BOOL WINAPI CryptGetDefaultProviderA (DWORD dwProvType, DWORD *pdwReserved,
		DWORD dwFlags, LPSTR pszProvName, DWORD *pcbProvName);
BOOL WINAPI CryptGetDefaultProviderW (DWORD dwProvType, DWORD *pdwReserved,
		DWORD dwFlags, LPWSTR pszProvName, DWORD *pcbProvName);
#define CryptGetDefaultProvider WINELIB_NAME_AW(CryptGetDefaultProvider)
BOOL WINAPI CryptGetUserKey (HCRYPTPROV hProv, DWORD dwKeySpec, HCRYPTKEY *phUserKey);
BOOL WINAPI CryptHashData (HCRYPTHASH hHash, BYTE *pbData, DWORD dwDataLen, DWORD dwFlags);
BOOL WINAPI CryptHashSessionKey (HCRYPTHASH hHash, HCRYPTKEY hKey, DWORD dwFlags);
BOOL WINAPI CryptImportKey (HCRYPTPROV hProv, BYTE *pbData, DWORD dwDataLen,
		HCRYPTKEY hPubKey, DWORD dwFlags, HCRYPTKEY *phKey);
BOOL WINAPI CryptRegisterOIDFunction(DWORD,LPCSTR,LPCSTR,LPCWSTR,LPCSTR);
BOOL WINAPI CryptReleaseContext (HCRYPTPROV hProv, DWORD dwFlags);
BOOL WINAPI CryptSetHashParam (HCRYPTHASH hHash, DWORD dwParam, BYTE *pbData, DWORD dwFlags);
BOOL WINAPI CryptSetKeyParam (HCRYPTKEY hKey, DWORD dwParam, BYTE *pbData, DWORD dwFlags);
BOOL WINAPI CryptSetOIDFunctionValue(DWORD dwEncodingType, LPCSTR pszFuncName,
                                     LPCSTR pszOID, LPCWSTR pwszValueName, DWORD dwValueType,
                                     const BYTE *pbValueData, DWORD cbValueData);
BOOL WINAPI CryptSetProviderA (LPCSTR pszProvName, DWORD dwProvType);
BOOL WINAPI CryptSetProviderW (LPCWSTR pszProvName, DWORD dwProvType);
#define CryptSetProvider WINELIB_NAME_AW(CryptSetProvider)
BOOL WINAPI CryptSetProviderExA (LPCSTR pszProvName, DWORD dwProvType, DWORD *pdwReserved, DWORD dwFlags);
BOOL WINAPI CryptSetProviderExW (LPCWSTR pszProvName, DWORD dwProvType, DWORD *pdwReserved, DWORD dwFlags);
#define CryptSetProviderEx WINELIB_NAME_AW(CryptSetProviderEx)
BOOL WINAPI CryptSetProvParam (HCRYPTPROV hProv, DWORD dwParam, BYTE *pbData, DWORD dwFlags);
BOOL WINAPI CryptSignHashA (HCRYPTHASH hHash, DWORD dwKeySpec, LPCSTR sDescription,
		DWORD dwFlags, BYTE *pbSignature, DWORD *pdwSigLen);
BOOL WINAPI CryptSignHashW (HCRYPTHASH hHash, DWORD dwKeySpec, LPCWSTR sDescription,
		DWORD dwFlags, BYTE *pbSignature, DWORD *pdwSigLen);
#define CryptSignHash WINELIB_NAME_AW(CryptSignHash)
BOOL WINAPI CryptUnregisterOIDFunction(DWORD,LPCSTR,LPCSTR);
BOOL WINAPI CryptVerifySignatureA (HCRYPTHASH hHash, BYTE *pbSignature, DWORD dwSigLen,
		HCRYPTKEY hPubKey, LPCSTR sDescription, DWORD dwFlags);
BOOL WINAPI CryptVerifySignatureW (HCRYPTHASH hHash, BYTE *pbSignature, DWORD dwSigLen,
		HCRYPTKEY hPubKey, LPCWSTR sDescription, DWORD dwFlags);
#define CryptVerifySignature WINELIB_NAME_AW(CryptVerifySignature)

/* cert store functions */
HCERTSTORE WINAPI CertOpenStore(LPCSTR lpszStoreProvider, DWORD dwEncodingType,
 HCRYPTPROV hCryptProv, DWORD dwFlags, const void *pvPara);

HCERTSTORE WINAPI CertOpenSystemStoreA(HCRYPTPROV hProv,
 LPCSTR szSubSystemProtocol);
HCERTSTORE WINAPI CertOpenSystemStoreW(HCRYPTPROV hProv,
 LPCWSTR szSubSystemProtocol);
#define CertOpenSystemStore WINELIB_NAME_AW(CertOpenSystemStore)

PCCERT_CONTEXT WINAPI CertEnumCertificatesInStore(HCERTSTORE hCertStore, PCCERT_CONTEXT pPrev);

BOOL WINAPI CertEnumSystemStoreLocation(DWORD dwFlags, void *pvArg,
 PFN_CERT_ENUM_SYSTEM_STORE_LOCATION pfnEnum);

BOOL WINAPI CertEnumSystemStore(DWORD dwFlags, void *pvSystemStoreLocationPara,
 void *pvArg, PFN_CERT_ENUM_SYSTEM_STORE pfnEnum);

BOOL WINAPI CertEnumPhysicalStore(const void *pvSystemStore, DWORD dwFlags,
 void *pvArg, PFN_CERT_ENUM_PHYSICAL_STORE pfnEnum);

BOOL WINAPI CertSaveStore(HCERTSTORE hCertStore, DWORD dwMsgAndCertEncodingType,
             DWORD dwSaveAs, DWORD dwSaveTo, void* pvSaveToPara, DWORD dwFlags);

PCCRL_CONTEXT WINAPI CertCreateCRLContext( DWORD dwCertEncodingType,
  const BYTE* pbCrlEncoded, DWORD cbCrlEncoded);

BOOL WINAPI CertAddStoreToCollection(HCERTSTORE hCollectionStore,
 HCERTSTORE hSiblingStore, DWORD dwUpdateFlags, DWORD dwPriority);

void WINAPI CertRemoveStoreFromCollection(HCERTSTORE hCollectionStore,
 HCERTSTORE hSiblingStore);

PCCERT_CHAIN_CONTEXT WINAPI CertFindChainInStore(HCERTSTORE hCertStore,
 DWORD dwCertEncodingType, DWORD dwFindFlags, DWORD dwFindType,
 const void *pvFindPara, PCCERT_CHAIN_CONTEXT pPrevChainContext);

BOOL WINAPI CertVerifyCertificateChainPolicy(LPCSTR szPolicyOID,
 PCCERT_CHAIN_CONTEXT pChainContext, PCERT_CHAIN_POLICY_PARA pPolicyPara,
 PCERT_CHAIN_POLICY_STATUS pPolicyStatus);

BOOL WINAPI CertCloseStore( HCERTSTORE hCertStore, DWORD dwFlags );

BOOL WINAPI CertFreeCertificateContext( PCCERT_CONTEXT pCertContext );

BOOL WINAPI CryptEncodeObject(DWORD dwCertEncodingType, LPCSTR lpszStructType,
 const void *pvStructInfo, BYTE *pbEncoded, DWORD *pcbEncoded);
BOOL WINAPI CryptEncodeObjectEx(DWORD dwCertEncodingType, LPCSTR lpszStructType,
 const void *pvStructInfo, DWORD dwFlags, PCRYPT_ENCODE_PARA pEncodePara,
 BYTE *pbEncoded, DWORD *pcbEncoded);

BOOL WINAPI CryptDecodeObject(DWORD dwCertEncodingType, LPCSTR lpszStructType,
 const BYTE *pbEncoded, DWORD cbEncoded, DWORD dwFlags, void *pvStructInfo,
 DWORD *pcbStructInfo);
BOOL WINAPI CryptDecodeObjectEx(DWORD dwCertEncodingType, LPCSTR lpszStructType,
 const BYTE *pbEncoded, DWORD cbEncoded, DWORD dwFlags,
 PCRYPT_DECODE_PARA pDecodePara, void *pvStructInfo, DWORD *pcbStructInfo);

/* crypt32.dll functions */
BOOL WINAPI CryptProtectData( DATA_BLOB* pDataIn, LPCWSTR szDataDescr,
 DATA_BLOB* pOptionalEntropy, PVOID pvReserved,
 CRYPTPROTECT_PROMPTSTRUCT* pPromptStruct, DWORD dwFlags, DATA_BLOB* pDataOut );

BOOL WINAPI CryptUnprotectData( DATA_BLOB* pDataIn, LPWSTR* ppszDataDescr,
 DATA_BLOB* pOptionalEntropy, PVOID pvReserved,
 CRYPTPROTECT_PROMPTSTRUCT* pPromptStruct, DWORD dwFlags, DATA_BLOB* pDataOut );

#ifdef __cplusplus
}
#endif

#endif
