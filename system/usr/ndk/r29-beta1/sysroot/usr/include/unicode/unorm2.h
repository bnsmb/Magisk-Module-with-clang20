// © 2016 and later: Unicode, Inc. and others.
// License & terms of use: http://www.unicode.org/copyright.html
/*
*******************************************************************************
*
*   Copyright (C) 2009-2015, International Business Machines
*   Corporation and others.  All Rights Reserved.
*
*******************************************************************************
*   file name:  unorm2.h
*   encoding:   UTF-8
*   tab size:   8 (not used)
*   indentation:4
*
*   created on: 2009dec15
*   created by: Markus W. Scherer
*/

#ifndef __UNORM2_H__
#define __UNORM2_H__

/**
 * @addtogroup icu4c ICU4C
 * @{
 * \file
 * \brief C API: New API for Unicode Normalization.
 *
 * Unicode normalization functionality for standard Unicode normalization or
 * for using custom mapping tables.
 * All instances of UNormalizer2 are unmodifiable/immutable.
 * Instances returned by unorm2_getInstance() are singletons that must not be deleted by the caller.
 * For more details see the Normalizer2 C++ class.
 */

#include "unicode/utypes.h"
#include "unicode/stringoptions.h"

#if U_SHOW_CPLUSPLUS_API
#include "unicode/localpointer.h"
#endif   // U_SHOW_CPLUSPLUS_API

/**
 * Constants for normalization modes.
 * For details about standard Unicode normalization forms
 * and about the algorithms which are also used with custom mapping tables
 * see http://www.unicode.org/unicode/reports/tr15/
 * \xrefitem stable "Stable" "Stable List" ICU 4.4
 */
typedef enum {
    /**
     * Decomposition followed by composition.
     * Same as standard NFC when using an "nfc" instance.
     * Same as standard NFKC when using an "nfkc" instance.
     * For details about standard Unicode normalization forms
     * see http://www.unicode.org/unicode/reports/tr15/
     * \xrefitem stable "Stable" "Stable List" ICU 4.4
     */
    UNORM2_COMPOSE,
    /**
     * Map, and reorder canonically.
     * Same as standard NFD when using an "nfc" instance.
     * Same as standard NFKD when using an "nfkc" instance.
     * For details about standard Unicode normalization forms
     * see http://www.unicode.org/unicode/reports/tr15/
     * \xrefitem stable "Stable" "Stable List" ICU 4.4
     */
    UNORM2_DECOMPOSE,
    /**
     * "Fast C or D" form.
     * If a string is in this form, then further decomposition <i>without reordering</i>
     * would yield the same form as DECOMPOSE.
     * Text in "Fast C or D" form can be processed efficiently with data tables
     * that are "canonically closed", that is, that provide equivalent data for
     * equivalent text, without having to be fully normalized.
     * Not a standard Unicode normalization form.
     * Not a unique form: Different FCD strings can be canonically equivalent.
     * For details see http://www.unicode.org/notes/tn5/#FCD
     * \xrefitem stable "Stable" "Stable List" ICU 4.4
     */
    UNORM2_FCD,
    /**
     * Compose only contiguously.
     * Also known as "FCC" or "Fast C Contiguous".
     * The result will often but not always be in NFC.
     * The result will conform to FCD which is useful for processing.
     * Not a standard Unicode normalization form.
     * For details see http://www.unicode.org/notes/tn5/#FCC
     * \xrefitem stable "Stable" "Stable List" ICU 4.4
     */
    UNORM2_COMPOSE_CONTIGUOUS
} UNormalization2Mode;

/**
 * Result values for normalization quick check functions.
 * For details see http://www.unicode.org/reports/tr15/#Detecting_Normalization_Forms
 * \xrefitem stable "Stable" "Stable List" ICU 2.0
 */
typedef enum UNormalizationCheckResult {
  /**
   * The input string is not in the normalization form.
   * \xrefitem stable "Stable" "Stable List" ICU 2.0
   */
  UNORM_NO,
  /**
   * The input string is in the normalization form.
   * \xrefitem stable "Stable" "Stable List" ICU 2.0
   */
  UNORM_YES,
  /**
   * The input string may or may not be in the normalization form.
   * This value is only returned for composition forms like NFC and FCC,
   * when a backward-combining character is found for which the surrounding text
   * would have to be analyzed further.
   * \xrefitem stable "Stable" "Stable List" ICU 2.0
   */
  UNORM_MAYBE
} UNormalizationCheckResult;

/**
 * Opaque C service object type for the new normalization API.
 * \xrefitem stable "Stable" "Stable List" ICU 4.4
 */
struct UNormalizer2;
typedef struct UNormalizer2 UNormalizer2;  /**< C typedef for struct UNormalizer2. \xrefitem stable "Stable" "Stable List" ICU 4.4 */

#if !UCONFIG_NO_NORMALIZATION

/**
 * Returns a UNormalizer2 instance for Unicode NFC normalization.
 * Same as unorm2_getInstance(NULL, "nfc", UNORM2_COMPOSE, pErrorCode).
 * Returns an unmodifiable singleton instance. Do not delete it.
 * @param pErrorCode Standard ICU error code. Its input value must
 *                  pass the U_SUCCESS() test, or else the function returns
 *                  immediately. Check for U_FAILURE() on output or use with
 *                  function chaining. (See User Guide for details.)
 * @return the requested Normalizer2, if successful
 * \xrefitem stable "Stable" "Stable List" ICU 49
 */
U_CAPI const UNormalizer2 * U_EXPORT2
unorm2_getNFCInstance(UErrorCode *pErrorCode) __INTRODUCED_IN(31);



/**
 * Returns a UNormalizer2 instance for Unicode NFD normalization.
 * Same as unorm2_getInstance(NULL, "nfc", UNORM2_DECOMPOSE, pErrorCode).
 * Returns an unmodifiable singleton instance. Do not delete it.
 * @param pErrorCode Standard ICU error code. Its input value must
 *                  pass the U_SUCCESS() test, or else the function returns
 *                  immediately. Check for U_FAILURE() on output or use with
 *                  function chaining. (See User Guide for details.)
 * @return the requested Normalizer2, if successful
 * \xrefitem stable "Stable" "Stable List" ICU 49
 */
U_CAPI const UNormalizer2 * U_EXPORT2
unorm2_getNFDInstance(UErrorCode *pErrorCode) __INTRODUCED_IN(31);



/**
 * Returns a UNormalizer2 instance for Unicode NFKC normalization.
 * Same as unorm2_getInstance(NULL, "nfkc", UNORM2_COMPOSE, pErrorCode).
 * Returns an unmodifiable singleton instance. Do not delete it.
 * @param pErrorCode Standard ICU error code. Its input value must
 *                  pass the U_SUCCESS() test, or else the function returns
 *                  immediately. Check for U_FAILURE() on output or use with
 *                  function chaining. (See User Guide for details.)
 * @return the requested Normalizer2, if successful
 * \xrefitem stable "Stable" "Stable List" ICU 49
 */
U_CAPI const UNormalizer2 * U_EXPORT2
unorm2_getNFKCInstance(UErrorCode *pErrorCode) __INTRODUCED_IN(31);



/**
 * Returns a UNormalizer2 instance for Unicode NFKD normalization.
 * Same as unorm2_getInstance(NULL, "nfkc", UNORM2_DECOMPOSE, pErrorCode).
 * Returns an unmodifiable singleton instance. Do not delete it.
 * @param pErrorCode Standard ICU error code. Its input value must
 *                  pass the U_SUCCESS() test, or else the function returns
 *                  immediately. Check for U_FAILURE() on output or use with
 *                  function chaining. (See User Guide for details.)
 * @return the requested Normalizer2, if successful
 * \xrefitem stable "Stable" "Stable List" ICU 49
 */
U_CAPI const UNormalizer2 * U_EXPORT2
unorm2_getNFKDInstance(UErrorCode *pErrorCode) __INTRODUCED_IN(31);



/**
 * Returns a UNormalizer2 instance for Unicode toNFKC_Casefold() normalization
 * which is equivalent to applying the NFKC_Casefold mappings and then NFC.
 * See https://www.unicode.org/reports/tr44/#NFKC_Casefold
 *
 * Same as unorm2_getInstance(NULL, "nfkc_cf", UNORM2_COMPOSE, pErrorCode).
 * Returns an unmodifiable singleton instance. Do not delete it.
 * @param pErrorCode Standard ICU error code. Its input value must
 *                  pass the U_SUCCESS() test, or else the function returns
 *                  immediately. Check for U_FAILURE() on output or use with
 *                  function chaining. (See User Guide for details.)
 * @return the requested Normalizer2, if successful
 * \xrefitem stable "Stable" "Stable List" ICU 49
 */
U_CAPI const UNormalizer2 * U_EXPORT2
unorm2_getNFKCCasefoldInstance(UErrorCode *pErrorCode) __INTRODUCED_IN(31);









/**
 * Closes a UNormalizer2 instance from unorm2_openFiltered().
 * Do not close instances from unorm2_getInstance()!
 * @param norm2 UNormalizer2 instance to be closed
 * \xrefitem stable "Stable" "Stable List" ICU 4.4
 */
U_CAPI void U_EXPORT2
unorm2_close(UNormalizer2 *norm2) __INTRODUCED_IN(31);



#if U_SHOW_CPLUSPLUS_API

U_NAMESPACE_BEGIN

/**
 * \class LocalUNormalizer2Pointer
 * "Smart pointer" class, closes a UNormalizer2 via unorm2_close().
 * For most methods see the LocalPointerBase base class.
 *
 * @see LocalPointerBase
 * @see LocalPointer
 * \xrefitem stable "Stable" "Stable List" ICU 4.4
 */
U_DEFINE_LOCAL_OPEN_POINTER(LocalUNormalizer2Pointer, UNormalizer2, unorm2_close);

U_NAMESPACE_END

#endif

/**
 * Writes the normalized form of the source string to the destination string
 * (replacing its contents) and returns the length of the destination string.
 * The source and destination strings must be different buffers.
 * @param norm2 UNormalizer2 instance
 * @param src source string
 * @param length length of the source string, or -1 if NUL-terminated
 * @param dest destination string; its contents is replaced with normalized src
 * @param capacity number of UChars that can be written to dest
 * @param pErrorCode Standard ICU error code. Its input value must
 *                   pass the U_SUCCESS() test, or else the function returns
 *                   immediately. Check for U_FAILURE() on output or use with
 *                   function chaining. (See User Guide for details.)
 * @return dest
 * \xrefitem stable "Stable" "Stable List" ICU 4.4
 */
U_CAPI int32_t U_EXPORT2
unorm2_normalize(const UNormalizer2 *norm2,
                 const UChar *src, int32_t length,
                 UChar *dest, int32_t capacity,
                 UErrorCode *pErrorCode) __INTRODUCED_IN(31);


/**
 * Appends the normalized form of the second string to the first string
 * (merging them at the boundary) and returns the length of the first string.
 * The result is normalized if the first string was normalized.
 * The first and second strings must be different buffers.
 * @param norm2 UNormalizer2 instance
 * @param first string, should be normalized
 * @param firstLength length of the first string, or -1 if NUL-terminated
 * @param firstCapacity number of UChars that can be written to first
 * @param second string, will be normalized
 * @param secondLength length of the source string, or -1 if NUL-terminated
 * @param pErrorCode Standard ICU error code. Its input value must
 *                   pass the U_SUCCESS() test, or else the function returns
 *                   immediately. Check for U_FAILURE() on output or use with
 *                   function chaining. (See User Guide for details.)
 * @return first
 * \xrefitem stable "Stable" "Stable List" ICU 4.4
 */
U_CAPI int32_t U_EXPORT2
unorm2_normalizeSecondAndAppend(const UNormalizer2 *norm2,
                                UChar *first, int32_t firstLength, int32_t firstCapacity,
                                const UChar *second, int32_t secondLength,
                                UErrorCode *pErrorCode) __INTRODUCED_IN(31);


/**
 * Appends the second string to the first string
 * (merging them at the boundary) and returns the length of the first string.
 * The result is normalized if both the strings were normalized.
 * The first and second strings must be different buffers.
 * @param norm2 UNormalizer2 instance
 * @param first string, should be normalized
 * @param firstLength length of the first string, or -1 if NUL-terminated
 * @param firstCapacity number of UChars that can be written to first
 * @param second string, should be normalized
 * @param secondLength length of the source string, or -1 if NUL-terminated
 * @param pErrorCode Standard ICU error code. Its input value must
 *                   pass the U_SUCCESS() test, or else the function returns
 *                   immediately. Check for U_FAILURE() on output or use with
 *                   function chaining. (See User Guide for details.)
 * @return first
 * \xrefitem stable "Stable" "Stable List" ICU 4.4
 */
U_CAPI int32_t U_EXPORT2
unorm2_append(const UNormalizer2 *norm2,
              UChar *first, int32_t firstLength, int32_t firstCapacity,
              const UChar *second, int32_t secondLength,
              UErrorCode *pErrorCode) __INTRODUCED_IN(31);



/**
 * Gets the decomposition mapping of c.
 * Roughly equivalent to normalizing the String form of c
 * on a UNORM2_DECOMPOSE UNormalizer2 instance, but much faster, and except that this function
 * returns a negative value and does not write a string
 * if c does not have a decomposition mapping in this instance's data.
 * This function is independent of the mode of the UNormalizer2.
 * @param norm2 UNormalizer2 instance
 * @param c code point
 * @param decomposition String buffer which will be set to c's
 *                      decomposition mapping, if there is one.
 * @param capacity number of UChars that can be written to decomposition
 * @param pErrorCode Standard ICU error code. Its input value must
 *                   pass the U_SUCCESS() test, or else the function returns
 *                   immediately. Check for U_FAILURE() on output or use with
 *                   function chaining. (See User Guide for details.)
 * @return the non-negative length of c's decomposition, if there is one; otherwise a negative value
 * \xrefitem stable "Stable" "Stable List" ICU 4.6
 */
U_CAPI int32_t U_EXPORT2
unorm2_getDecomposition(const UNormalizer2 *norm2,
                        UChar32 c, UChar *decomposition, int32_t capacity,
                        UErrorCode *pErrorCode) __INTRODUCED_IN(31);



/**
 * Gets the raw decomposition mapping of c.
 *
 * This is similar to the unorm2_getDecomposition() function but returns the
 * raw decomposition mapping as specified in UnicodeData.txt or
 * (for custom data) in the mapping files processed by the gennorm2 tool.
 * By contrast, unorm2_getDecomposition() returns the processed,
 * recursively-decomposed version of this mapping.
 *
 * When used on a standard NFKC Normalizer2 instance,
 * unorm2_getRawDecomposition() returns the Unicode Decomposition_Mapping (dm) property.
 *
 * When used on a standard NFC Normalizer2 instance,
 * it returns the Decomposition_Mapping only if the Decomposition_Type (dt) is Canonical (Can);
 * in this case, the result contains either one or two code points (=1..4 UChars).
 *
 * This function is independent of the mode of the UNormalizer2.
 * @param norm2 UNormalizer2 instance
 * @param c code point
 * @param decomposition String buffer which will be set to c's
 *                      raw decomposition mapping, if there is one.
 * @param capacity number of UChars that can be written to decomposition
 * @param pErrorCode Standard ICU error code. Its input value must
 *                   pass the U_SUCCESS() test, or else the function returns
 *                   immediately. Check for U_FAILURE() on output or use with
 *                   function chaining. (See User Guide for details.)
 * @return the non-negative length of c's raw decomposition, if there is one; otherwise a negative value
 * \xrefitem stable "Stable" "Stable List" ICU 49
 */
U_CAPI int32_t U_EXPORT2
unorm2_getRawDecomposition(const UNormalizer2 *norm2,
                           UChar32 c, UChar *decomposition, int32_t capacity,
                           UErrorCode *pErrorCode) __INTRODUCED_IN(31);



/**
 * Performs pairwise composition of a & b and returns the composite if there is one.
 *
 * Returns a composite code point c only if c has a two-way mapping to a+b.
 * In standard Unicode normalization, this means that
 * c has a canonical decomposition to a+b
 * and c does not have the Full_Composition_Exclusion property.
 *
 * This function is independent of the mode of the UNormalizer2.
 * @param norm2 UNormalizer2 instance
 * @param a A (normalization starter) code point.
 * @param b Another code point.
 * @return The non-negative composite code point if there is one; otherwise a negative value.
 * \xrefitem stable "Stable" "Stable List" ICU 49
 */
U_CAPI UChar32 U_EXPORT2
unorm2_composePair(const UNormalizer2 *norm2, UChar32 a, UChar32 b) __INTRODUCED_IN(31);



/**
 * Gets the combining class of c.
 * The default implementation returns 0
 * but all standard implementations return the Unicode Canonical_Combining_Class value.
 * @param norm2 UNormalizer2 instance
 * @param c code point
 * @return c's combining class
 * \xrefitem stable "Stable" "Stable List" ICU 49
 */
U_CAPI uint8_t U_EXPORT2
unorm2_getCombiningClass(const UNormalizer2 *norm2, UChar32 c) __INTRODUCED_IN(31);



/**
 * Tests if the string is normalized.
 * Internally, in cases where the quickCheck() method would return "maybe"
 * (which is only possible for the two COMPOSE modes) this method
 * resolves to "yes" or "no" to provide a definitive result,
 * at the cost of doing more work in those cases.
 * @param norm2 UNormalizer2 instance
 * @param s input string
 * @param length length of the string, or -1 if NUL-terminated
 * @param pErrorCode Standard ICU error code. Its input value must
 *                   pass the U_SUCCESS() test, or else the function returns
 *                   immediately. Check for U_FAILURE() on output or use with
 *                   function chaining. (See User Guide for details.)
 * @return true if s is normalized
 * \xrefitem stable "Stable" "Stable List" ICU 4.4
 */
U_CAPI UBool U_EXPORT2
unorm2_isNormalized(const UNormalizer2 *norm2,
                    const UChar *s, int32_t length,
                    UErrorCode *pErrorCode) __INTRODUCED_IN(31);



/**
 * Tests if the string is normalized.
 * For the two COMPOSE modes, the result could be "maybe" in cases that
 * would take a little more work to resolve definitively.
 * Use spanQuickCheckYes() and normalizeSecondAndAppend() for a faster
 * combination of quick check + normalization, to avoid
 * re-checking the "yes" prefix.
 * @param norm2 UNormalizer2 instance
 * @param s input string
 * @param length length of the string, or -1 if NUL-terminated
 * @param pErrorCode Standard ICU error code. Its input value must
 *                   pass the U_SUCCESS() test, or else the function returns
 *                   immediately. Check for U_FAILURE() on output or use with
 *                   function chaining. (See User Guide for details.)
 * @return UNormalizationCheckResult
 * \xrefitem stable "Stable" "Stable List" ICU 4.4
 */
U_CAPI UNormalizationCheckResult U_EXPORT2
unorm2_quickCheck(const UNormalizer2 *norm2,
                  const UChar *s, int32_t length,
                  UErrorCode *pErrorCode) __INTRODUCED_IN(31);



/**
 * Returns the end of the normalized substring of the input string.
 * In other words, with <code>end=spanQuickCheckYes(s, ec);</code>
 * the substring <code>UnicodeString(s, 0, end)</code>
 * will pass the quick check with a "yes" result.
 *
 * The returned end index is usually one or more characters before the
 * "no" or "maybe" character: The end index is at a normalization boundary.
 * (See the class documentation for more about normalization boundaries.)
 *
 * When the goal is a normalized string and most input strings are expected
 * to be normalized already, then call this method,
 * and if it returns a prefix shorter than the input string,
 * copy that prefix and use normalizeSecondAndAppend() for the remainder.
 * @param norm2 UNormalizer2 instance
 * @param s input string
 * @param length length of the string, or -1 if NUL-terminated
 * @param pErrorCode Standard ICU error code. Its input value must
 *                   pass the U_SUCCESS() test, or else the function returns
 *                   immediately. Check for U_FAILURE() on output or use with
 *                   function chaining. (See User Guide for details.)
 * @return "yes" span end index
 * \xrefitem stable "Stable" "Stable List" ICU 4.4
 */
U_CAPI int32_t U_EXPORT2
unorm2_spanQuickCheckYes(const UNormalizer2 *norm2,
                         const UChar *s, int32_t length,
                         UErrorCode *pErrorCode) __INTRODUCED_IN(31);



/**
 * Tests if the character always has a normalization boundary before it,
 * regardless of context.
 * For details see the Normalizer2 base class documentation.
 * @param norm2 UNormalizer2 instance
 * @param c character to test
 * @return true if c has a normalization boundary before it
 * \xrefitem stable "Stable" "Stable List" ICU 4.4
 */
U_CAPI UBool U_EXPORT2
unorm2_hasBoundaryBefore(const UNormalizer2 *norm2, UChar32 c) __INTRODUCED_IN(31);



/**
 * Tests if the character always has a normalization boundary after it,
 * regardless of context.
 * For details see the Normalizer2 base class documentation.
 * @param norm2 UNormalizer2 instance
 * @param c character to test
 * @return true if c has a normalization boundary after it
 * \xrefitem stable "Stable" "Stable List" ICU 4.4
 */
U_CAPI UBool U_EXPORT2
unorm2_hasBoundaryAfter(const UNormalizer2 *norm2, UChar32 c) __INTRODUCED_IN(31);



/**
 * Tests if the character is normalization-inert.
 * For details see the Normalizer2 base class documentation.
 * @param norm2 UNormalizer2 instance
 * @param c character to test
 * @return true if c is normalization-inert
 * \xrefitem stable "Stable" "Stable List" ICU 4.4
 */
U_CAPI UBool U_EXPORT2
unorm2_isInert(const UNormalizer2 *norm2, UChar32 c) __INTRODUCED_IN(31);





#endif  /* !UCONFIG_NO_NORMALIZATION */
#endif  /* __UNORM2_H__ */

/** @} */ // addtogroup
