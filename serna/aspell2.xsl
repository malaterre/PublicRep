<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="text" indent="yes"/>
  <xsl:key name="ptid" match="PointerType" use="@id"/>
  <xsl:key name="sid" match="Struct" use="@id"/>
  <xsl:key name="ftid" match="FundamentalType" use="@id"/>
  <xsl:key name="cqtid" match="CvQualifiedType" use="@id"/>
  <xsl:template match="/">
    <xsl:text>
#ifndef ASPELL_HPP_
#define ASPELL_HPP_

// This file has been generated automatically

#include "FunTraits.h"
#include "DynFunctor.h"
#include "aspell.h"

#define SYM(x) extern const char nm_##x[];

</xsl:text>
    <xsl:for-each select="GCC_XML/Function">
      <!--xsl:sort select="@name"/-->
      <xsl:if test="not(@attributes != '')">
        <xsl:text>SYM(</xsl:text>
        <xsl:value-of select="@name"/>
        <xsl:text>);
</xsl:text>
        <xsl:text>REGISTER_TYPEOF(</xsl:text>
        <!--xsl:value-of select="@returns"/-->
        <xsl:for-each select="key('ftid',@returns)">
          <xsl:value-of select="@name"/>
        </xsl:for-each>
        <xsl:text> (</xsl:text>
        <xsl:variable name="ptr_arg">
          <xsl:for-each select="Argument">
            <!--xsl:value-of select="@type"/-->
            <xsl:text> </xsl:text>
            <xsl:for-each select="key('ptid',@type)">
              <xsl:for-each select="key('cqtid',@type)">
                <xsl:text> const </xsl:text>
                <!--xsl:apply-templates select="key('bib',$name)"/-->
                <xsl:for-each select="key('ftid',@type)">
                  <xsl:value-of select="@name"/>
                </xsl:for-each>
                <xsl:for-each select="key('sid',@type)">
                  <xsl:value-of select="@name"/>
                </xsl:for-each>
              </xsl:for-each>
              <xsl:text>*</xsl:text>
            </xsl:for-each>
            <xsl:text>,</xsl:text>
          </xsl:for-each>
        </xsl:variable>
        <xsl:value-of select="$ptr_arg"/>
        <xsl:text> 1);

</xsl:text>
      </xsl:if>
    </xsl:for-each>
  </xsl:template>
</xsl:stylesheet>
