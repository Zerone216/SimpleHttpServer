
/**
 * `uri.h' - uri.c
 */

#ifndef URI_H
#define URI_H 1

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Encodes a URI component by replacing each
 * instance of certain characters by one, two, three, or four escape
 * sequences representing the UTF-8 encoding of the character
 */

char *
uri_encode (const char *);

/**
 * Decodes a URI component source from `uri_encode'
 */

char *
uri_decode (const char *);

#ifdef __cplusplus
}
#endif

#endif // URI_H
