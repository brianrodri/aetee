// <Copyright Holder>. Copyright (C) <Copyright Year(s)>. <License>
#ifndef HEADER_AETEE_VERSION_H_INCLUDED
#define HEADER_AETEE_VERSION_H_INCLUDED

#ifdef __cplusplus
#   define EXTERNC extern "C"
#else
#   define EXTERNC
#endif

EXTERNC int aetee_version_major();
EXTERNC int aetee_version_minor();
EXTERNC int aetee_version_patch();

#endif
