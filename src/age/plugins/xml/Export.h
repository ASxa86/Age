#pragma once

#ifdef WIN32
#ifdef Age_XML_Export
#define AGE_XML_EXPORT __declspec(dllexport)
#define AGE_XML_EXPORT_C extern "C" __declspec(dllexport)
#else
#define AGE_XML_EXPORT __declspec(dllimport)
#define AGE_XML_EXPORT_C extern "C" __declspec(dllimport)
#endif
#else
#define AGE_XML_EXPORT
#define AGE_XML_EXPORT_C extern "C"
#endif
