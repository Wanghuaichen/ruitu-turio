#ifndef _TYPE_H_
#define _TYPE_H_
#include "include.h"
#define MAX_SOCK_NUM    8 /**< Maxmium number of socket  */

typedef char int8;
//
//  typedef volatile char vint8;
//
//  typedef unsigned char uint8;
//
//  typedef volatile unsigned char vuint8;
//
typedef int int16;
//
//  typedef unsigned short uint16;
//
typedef long int32;

//
//  typedef unsigned long uint32;

typedef uint8_t       u_char;   /**< 8-bit value */
typedef uint8_t       SOCKET;
typedef uint16_t      u_short;  /**< 16-bit value */
typedef uint16_t      u_int;    /**< 16-bit value */
typedef uint32_t      u_long;   /**< 32-bit value */

typedef union _un_l2cval
{
  uint32_t  lVal;
  uint8_t  cVal[4];
}un_l2cval;

typedef union _un_i2cval
{
  uint16_t iVal;
  uint8_t  cVal[2];
}un_i2cval;

#endif    /* _TYPE_H_ */
