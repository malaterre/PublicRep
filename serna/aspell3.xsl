<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="text" indent="yes"/>
  <xsl:variable name="fundamental_types" select="GCC_XML/FundamentalType"/>
  <xsl:variable name="pointer_types" select="GCC_XML/PointerType"/>
  <xsl:variable name="struct_types" select="GCC_XML/Struct"/>
  <xsl:variable name="cvqualified_types" select="GCC_XML/CvQualifiedType"/>
  <xsl:variable name="type_defs" select="GCC_XML/Typedef[@name='CvMat']"/>
  <xsl:template match="GCC_XML">
    <xsl:text>#ifndef ASPELL_HPP_
#define ASPELL_HPP_

// This file has been generated automatically

#include "FunTraits.h"
#include "DynFunctor.h"
#include "aspell.h"

#define SYM(x) extern const char nm_##x[];

</xsl:text>
    <xsl:variable name="functions" select="//Function"/>
    <xsl:for-each select="$functions">
      <xsl:if test="not(@attributes != '')">
        <xsl:variable name="return_type">
          <xsl:call-template name="get_type">
            <xsl:with-param name="tid" select="@returns"/>
          </xsl:call-template>
        </xsl:variable>
        <xsl:text>SYM(</xsl:text>
        <xsl:value-of select="@name"/>
        <xsl:text>);
</xsl:text>
        <xsl:text>REGISTER_TYPEOF(</xsl:text>
        <xsl:value-of select="$return_type"/>
        <xsl:text> (</xsl:text>
        <xsl:for-each select="Argument">
          <xsl:variable name="argument_type">
            <xsl:call-template name="get_type">
              <xsl:with-param name="tid" select="@type"/>
            </xsl:call-template>
          </xsl:variable>
          <xsl:if test="position()!=1">, </xsl:if>
          <xsl:value-of select="$argument_type"/>
        </xsl:for-each>
        <xsl:text>), </xsl:text>
        <xsl:value-of select="position()"/>
        <xsl:text>);</xsl:text>
        <xsl:text>

</xsl:text>
      </xsl:if>
    </xsl:for-each>
    <xsl:text>#undef SYM

#endif // ASPELL_HPP_
</xsl:text>
  </xsl:template>
  <xsl:template name="get_type">
    <xsl:param name="tid"/>
    <xsl:choose>
      <xsl:when test="$fundamental_types[@id=$tid]">
        <xsl:value-of select="$fundamental_types[@id=$tid]/@name"/>
      </xsl:when>
      <xsl:when test="$struct_types[@id=$tid]">
        <xsl:choose>
          <xsl:when test="$type_defs[@id=$pointer_types[@id=$tid]/@type]">
            <xsl:value-of select="$type_defs[@id=$pointer_types[@id=$tid]/@type]/@name"/>
            <xsl:text> *</xsl:text>
          </xsl:when>
          <xsl:when test="$fundamental_types[@id=$pointer_types[@id=$tid]/@type]">
            <xsl:value-of select="$fundamental_types[@id=$pointer_types[@id=$tid]/@type]/@name"/>
            <xsl:text> *</xsl:text>
          </xsl:when>
          <xsl:otherwise>no type found 2</xsl:otherwise>
        </xsl:choose>
      </xsl:when>
      <xsl:when test="$pointer_types[@id=$tid]">
        <xsl:choose>
          <xsl:when test="$cvqualified_types[@id=$pointer_types[@id=$tid]/@type]">
            <xsl:variable name="intermediate_type" select="$cvqualified_types[@id=$pointer_types[@id=$tid]/@type]/@type"/>
            <!--xsl:value-of select="$cvqualified_types[@id=$pointer_types[@id=$tid]/@type]/@name"/-->
            <!--xsl:value-of select="$my"/-->
            <xsl:text>const </xsl:text>
            <xsl:choose>
              <xsl:when test="$fundamental_types[@id=$intermediate_type]">
                <xsl:value-of select="$fundamental_types[@id=$intermediate_type]/@name"/>
              </xsl:when>
              <xsl:otherwise>no type found 4 <xsl:value-of select="$intermediate_type"/></xsl:otherwise>
            </xsl:choose>
            <xsl:text> *</xsl:text>
          </xsl:when>
          <xsl:when test="$struct_types[@id=$pointer_types[@id=$tid]/@type]">
            <xsl:value-of select="$struct_types[@id=$pointer_types[@id=$tid]/@type]/@name"/>
            <xsl:text> *</xsl:text>
          </xsl:when>
          <xsl:when test="$type_defs[@id=$pointer_types[@id=$tid]/@type]">
            <xsl:value-of select="$type_defs[@id=$pointer_types[@id=$tid]/@type]/@name"/>
            <xsl:text> *</xsl:text>
          </xsl:when>
          <xsl:when test="$fundamental_types[@id=$pointer_types[@id=$tid]/@type]">
            <xsl:value-of select="$fundamental_types[@id=$pointer_types[@id=$tid]/@type]/@name"/>
            <xsl:text> *</xsl:text>
          </xsl:when>
          <xsl:otherwise>no type found 3 <xsl:value-of select="$tid"/></xsl:otherwise>
        </xsl:choose>
      </xsl:when>
      <xsl:when test="$type_defs[@id=$tid]">
        <xsl:value-of select="$type_defs[@id=$tid]/@name"/>
      </xsl:when>
      <xsl:otherwise>no type found 1 <xsl:value-of select="$tid"/></xsl:otherwise>
    </xsl:choose>
  </xsl:template>
</xsl:stylesheet>
