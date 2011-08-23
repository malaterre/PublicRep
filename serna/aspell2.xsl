<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="text" indent="yes"/>
  <xsl:key name="ptid" match="PointerType" use="@id"/>
  <xsl:key name="sid" match="Struct" use="@id"/>
  <xsl:key name="ftid" match="FundamentalType" use="@id"/>
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
        <xsl:text>)
</xsl:text>
        <xsl:for-each select="Argument">
          <!--xsl:value-of select="@type"/-->
        <xsl:text>REGISTER_TYPEOF( </xsl:text>
          <xsl:for-each select="key('ptid',@type)">
            <!--xsl:value-of select="@type"/-->
            <xsl:for-each select="key('sid',@type)">
        <xsl:text>(</xsl:text>
              <xsl:value-of select="@name"/>
        <xsl:text> *),</xsl:text>
            </xsl:for-each>
          </xsl:for-each>
        </xsl:for-each>
        <xsl:text>1);
</xsl:text>
      </xsl:if>
    </xsl:for-each>
  </xsl:template>
</xsl:stylesheet>
