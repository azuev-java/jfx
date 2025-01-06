/*
 * Copyright (c) 2024, Oracle and/or its affiliates. All rights reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.  Oracle designates this
 * particular file as subject to the "Classpath" exception as provided
 * by Oracle in the LICENSE file that accompanied this code.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
 * or visit www.oracle.com if you need additional information or have any
 * questions.
 */

#import "JFXNavigableTextAccessibility.h"
#import "GlassMacros.h"
#import "GlassAccessible.h"
#import "com_sun_glass_ui_mac_MacAccessible.h"
#import "com_sun_glass_ui_mac_MacVariant.h"
#import "common.h"

@implementation JFXNavigableTextAccessibility
- (NSAccessibilityRole)accessibilityRole
{
//    NSLog(@"Asked for the role for %@", [self getJavaRole]);
    if ([@"TEXT_FIELD" isEqualToString:[self getJavaRole]]) {
        return NSAccessibilityTextFieldRole;
    }
    return NSAccessibilityTextAreaRole;
}

- (NSAccessibilitySubrole)accessibilitySubrole
{
    jobject jresult = NULL;
    GET_MAIN_JENV;
    if (env == NULL) return NULL;
    jresult = (jobject)(*env)->CallLongMethod(env, [self getJAccessible],
                                              jAccessibilityAttributeValue, (jlong)@"AXSubrole");
    GLASS_CHECK_EXCEPTION(env);
    if (variantToID(env, jresult) == NULL) {
        return NULL;
    }
    return NSAccessibilitySecureTextFieldSubrole;
}

- (id)accessibilityParent
{
    return [super accessibilityParent];
}

- (BOOL)isAccessibilityEnabled
{
    return TRUE;
}

- (NSArray *)accessibilitySharedFocusElements
{
    return NULL;
}

- (BOOL)isAccessibilityEdited {
    return TRUE;
}

- (NSArray *)accessibilityChildren
{
    return [super accessibilityChildren];
//    return NULL;
}

- (NSRect)accessibilityFrame
{
    return [super accessibilityFrame];
}

- (NSString *)accessibilityValue
{
    NSLog(@"Getting value as %@", [super accessibilityValue]);
    return [super accessibilityValue];
}

- (nullable NSString *)accessibilityStringForRange:(NSRange)range
{
    id parameter = [NSValue valueWithRange:range];
    jobject jresult = NULL;
    GET_MAIN_JENV;
    if (env == NULL) return NULL;
    jresult = (jobject)(*env)->CallLongMethod(env, [self getJAccessible],
                                              jAccessibilityAttributeValueForParameter,
                                              (jlong)@"AXStringForRange", (jlong)parameter);
    GLASS_CHECK_EXCEPTION(env);
    NSString * ret = (NSString *)variantToID(env, jresult);
    NSLog(@"accessibilityStringForRange(%@) returns %@", parameter, ret);
    return ret;
}

- (NSInteger)accessibilityLineForIndex:(NSInteger)index
{
    id parameter = [NSNumber numberWithInteger:index];
    jobject jresult = NULL;
    GET_MAIN_JENV;
    if (env == NULL) return 0;
    jresult = (jobject)(*env)->CallLongMethod(env, [self getJAccessible],
                                              jAccessibilityAttributeValueForParameter,
                                              (jlong)@"AXLineForIndex", (jlong)parameter);
    GLASS_CHECK_EXCEPTION(env);
    NSInteger ret = [variantToID(env, jresult) integerValue];
    NSLog(@"accessibilityLineForIndex(%@) returns %@", parameter, variantToID(env, jresult));
    return ret;
}

- (NSRange)accessibilityRangeForLine:(NSInteger)lineNumber
{
    id parameter = [NSNumber numberWithInteger:lineNumber];
    jobject jresult = NULL;
    GET_MAIN_JENV;
    if (env == NULL) return EmptyRange;
    jresult = (jobject)(*env)->CallLongMethod(env, [self getJAccessible],
                                              jAccessibilityAttributeValueForParameter,
                                              (jlong)@"AXRangeForLine", (jlong)parameter);
    GLASS_CHECK_EXCEPTION(env);
    NSRange ret = [variantToID(env, jresult) rangeValue];
    NSLog(@"accessibilityRangeForLine(%@) returns %@", parameter, variantToID(env, jresult));
    return ret;
}

- (NSRect)accessibilityFrameForRange:(NSRange)range
{
    id parameter = [NSValue valueWithRange:range];
    jobject jresult = NULL;
    GET_MAIN_JENV;
    if (env == NULL) return NSZeroRect;
    jresult = (jobject)(*env)->CallLongMethod(env, [self getJAccessible],
                                              jAccessibilityAttributeValueForParameter,
                                              (jlong)@"AXBoundsForRange", (jlong)parameter);
    GLASS_CHECK_EXCEPTION(env);
    NSLog(@"accessibilityFrameForRange(%@) returns %@", parameter, variantToID(env, jresult));
    return [variantToID(env, jresult) rectValue];
}

- (NSInteger)accessibilityNumberOfCharacters
{
    jobject jresult = NULL;
    GET_MAIN_JENV;
    if (env == NULL) return 0;
    jresult = (jobject)(*env)->CallLongMethod(env, [self getJAccessible],
                                              jAccessibilityAttributeValue, (jlong)@"AXNumberOfCharacters");
    GLASS_CHECK_EXCEPTION(env);
    NSLog(@"accessibilityNumberOfCharacters returns %@", variantToID(env, jresult));
    return [variantToID(env, jresult) integerValue];
}

- (NSRange)accessibilitySelectedTextRange
{
    jobject jresult = NULL;
    GET_MAIN_JENV;
    if (env == NULL) return EmptyRange;
    jresult = (jobject)(*env)->CallLongMethod(env, [self getJAccessible],
                                              jAccessibilityAttributeValue, (jlong)@"AXSelectedTextRange");
    GLASS_CHECK_EXCEPTION(env);
    NSRange ret = [variantToID(env, jresult) rangeValue];
    NSLog(@"accessibilitySelectedTextRange returns %@", variantToID(env, jresult));
    return ret;
}

//- (NSString *)accessibilitySelectedText
//{
//    id parameter = [NSValue valueWithRange:[self accessibilitySelectedTextRange]];
//    jobject jresult = NULL;
//    GET_MAIN_JENV;
//    if (env == NULL) return NULL;
//    jresult = (jobject)(*env)->CallLongMethod(env, [self getJAccessible],
//                                              jAccessibilityAttributeValueForParameter,
//                                              (jlong)@"AXStringForRange", (jlong)parameter);
//    GLASS_CHECK_EXCEPTION(env);
//    NSString * ret = (NSString *)variantToID(env, jresult);
//    NSLog(@"accessibilitySelectedText returns %@", ret);
//    return ret;
//}

- (NSRange)accessibilityVisibleCharacterRange
{
    jobject jresult = NULL;
    GET_MAIN_JENV;
    if (env == NULL) return NSMakeRange(0, 0);;
    jresult = (jobject)(*env)->CallLongMethod(env, [self getJAccessible],
                                              jAccessibilityAttributeValue, (jlong)@"AXVisibleCharacterRange");
    GLASS_CHECK_EXCEPTION(env);
    return [variantToID(env, jresult) rangeValue];
}

- (NSAttributedString *) accessibilityAttributedStringForRange:(NSRange)range
{
    id parameter = [NSValue valueWithRange:range];
    jobject jresult = NULL;
    GET_MAIN_JENV;
    if (env == NULL) return NULL;
    jresult = (jobject)(*env)->CallLongMethod(env, [self getJAccessible],
                                              jAccessibilityAttributeValueForParameter,
                                              (jlong)@"AXAttributedStringForRange", (jlong)parameter);
    GLASS_CHECK_EXCEPTION(env);
    NSAttributedString * retval = variantToID(env, jresult);
    NSLog(@"Returning attributedSubString: %@", retval);
    return retval;
}

@end