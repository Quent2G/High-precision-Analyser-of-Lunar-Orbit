/*

-Procedure isrchc_c  ( Search in a character array )

-Abstract

   Search for a given value within a character string array. Return
   the index of the first matching array entry, or -1 if the key
   value was not found.

-Disclaimer

   THIS SOFTWARE AND ANY RELATED MATERIALS WERE CREATED BY THE
   CALIFORNIA INSTITUTE OF TECHNOLOGY (CALTECH) UNDER A U.S.
   GOVERNMENT CONTRACT WITH THE NATIONAL AERONAUTICS AND SPACE
   ADMINISTRATION (NASA). THE SOFTWARE IS TECHNOLOGY AND SOFTWARE
   PUBLICLY AVAILABLE UNDER U.S. EXPORT LAWS AND IS PROVIDED "AS-IS"
   TO THE RECIPIENT WITHOUT WARRANTY OF ANY KIND, INCLUDING ANY
   WARRANTIES OF PERFORMANCE OR MERCHANTABILITY OR FITNESS FOR A
   PARTICULAR USE OR PURPOSE (AS SET FORTH IN UNITED STATES UCC
   SECTIONS 2312-2313) OR FOR ANY PURPOSE WHATSOEVER, FOR THE
   SOFTWARE AND RELATED MATERIALS, HOWEVER USED.

   IN NO EVENT SHALL CALTECH, ITS JET PROPULSION LABORATORY, OR NASA
   BE LIABLE FOR ANY DAMAGES AND/OR COSTS, INCLUDING, BUT NOT
   LIMITED TO, INCIDENTAL OR CONSEQUENTIAL DAMAGES OF ANY KIND,
   INCLUDING ECONOMIC DAMAGE OR INJURY TO PROPERTY AND LOST PROFITS,
   REGARDLESS OF WHETHER CALTECH, JPL, OR NASA BE ADVISED, HAVE
   REASON TO KNOW, OR, IN FACT, SHALL KNOW OF THE POSSIBILITY.

   RECIPIENT BEARS ALL RISK RELATING TO QUALITY AND PERFORMANCE OF
   THE SOFTWARE AND ANY RELATED MATERIALS, AND AGREES TO INDEMNIFY
   CALTECH AND NASA FOR ALL THIRD-PARTY CLAIMS RESULTING FROM THE
   ACTIONS OF RECIPIENT IN THE USE OF THE SOFTWARE.

-Required_Reading

   None.

-Keywords

   ARRAY
   SEARCH

*/

   #include "SpiceUsr.h"
   #include "SpiceZfc.h"
   #include "SpiceZst.h"
   #include "SpiceZmc.h"
   #include "f2cMang.h"
   #undef    isrchc_c


   SpiceInt isrchc_c ( ConstSpiceChar  * value,
                       SpiceInt          ndim,
                       SpiceInt          arrlen,
                       const void      * array   )

/*

-Brief_I/O

   VARIABLE  I/O  DESCRIPTION
   --------  ---  --------------------------------------------------
   value      I   Key value to be found in array.
   ndim       I   Dimension of array.
   arrlen     I   String length.
   array      I   Character string array to search.

   The function returns the index of the first matching array
   element or -1 if the value is not found.

-Detailed_Input

   value       is the key value to be found in the array. Trailing
               blanks in this key are not significant: string matches
               found by this routine do not require trailing blanks in
               value to match those in the corresponding element of
               array.

               The input key `value' may have length zero.

   ndim        is the dimension of the array.

   arrlen      is the declared length of the strings in the input
               string array, including null terminators. The input
               array should be declared with dimension

                  [ndim][arrlen]

   array       is the array of character strings to be searched. Trailing
               blanks in the strings in this array are not significant.

-Detailed_Output

   The function returns the index of the first matching array
   element in array. If value is not found, isrchc_c returns -1.

-Parameters

   None.

-Exceptions

   1)  If ndim < 1, the function value is -1.

   2)  If the `value' input string pointer is null, the error
       SPICE(NULLPOINTER) is signaled. The function returns the value
       -1.

   3)  If the `array' input array pointer is null, the error
       SPICE(NULLPOINTER) is signaled. The function returns the value
       -1.

   4)  If the `array' input array strings have length less than two
       characters, the error SPICE(STRINGTOOSHORT) is signaled. The
       function returns the value -1.

-Files

   None.

-Particulars

   None.

-Examples

   The following table shows the value of isrchc_c given the contents
   of array and value:

      array                 value     isrchc_c
    -----------------       -----     --------
    "1", "0", "4", "2"       "4"          2
    "1", "0", "4", "2"       "2"          3
    "1", "0", "4", "2"       "3"         -1

-Restrictions

   1)  String comparisons performed by this routine are Fortran-style:
       trailing blanks in the input array or key value are ignored.
       This gives consistent behavior with CSPICE code generated by
       the f2c translator, as well as with the Fortran SPICE Toolkit.

       Note that this behavior is not identical to that of the ANSI
       C library functions strcmp and strncmp.

-Literature_References

   None.

-Author_and_Institution

   N.J. Bachman        (JPL)
   J. Diaz del Rio     (ODC Space)
   W.M. Owen           (JPL)

-Version

   -CSPICE Version 1.2.0, 03-AUG-2021 (JDR)

       Changed the input argument name "lenvals" to "arrlen" for consistency
       with other routines.

       Edited the header to comply with NAIF standard.

       Removed entry #3 from -Exceptions section and edited the description of
       "value" in -Detailed_Input to indicate that empty string values are
       allowed.

   -CSPICE Version 1.1.0, 07-MAR-2009 (NJB)

       This file now includes the header file f2cMang.h.
       This header supports name mangling of f2c library
       functions.

       Header sections were re-ordered.

   -CSPICE Version 1.0.0, 22-JUL-2002 (NJB) (WMO)

-Index_Entries

   search in a character array

-&
*/

{ /* Begin isrchc_c */


   /*
   f2c library utility prototypes
   */
   extern integer   s_cmp  (char *a, char *b, ftnlen la, ftnlen lb );

   /*
   Local macros
   */
   #define ARRAY( i )     (  ( (SpiceChar *)array ) + i*arrlen  )

   /*
   Local variables
   */
   SpiceInt                i;


   /*
   Use discovery check-in.

   Return immediately if the array dimension is non-positive.
   */
   if ( ndim < 1 )
   {
      return ( -1 );
   }


   /*
   Make sure the input pointer for the key value is non-null
   and that the length is adequate.
   */
   CHKPTR_VAL ( CHK_DISCOVER, "isrchc_c", value, -1 );


   /*
   Make sure the input pointer for the string array is non-null
   and that the length `arrlen' is sufficient.
   */
   CHKOSTR_VAL ( CHK_DISCOVER, "isrchc_c", array, arrlen, -1 );


   for ( i = 0;  i < ndim;  i++ )
   {
      if (  s_cmp ( (char   *) value,
                    (char   *) ARRAY(i),
                    (ftnlen  ) strlen(value),
                    (ftnlen  ) strlen(ARRAY(i)) )  == 0  )
      {
         return ( i );
      }
   }

   /*
   Indicate no match was found.
   */
   return ( -1 );


} /* End isrchc_c */
