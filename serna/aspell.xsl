<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="text" indent="yes"/>
<!-- The main template that loop over all dict/entry -->
  <xsl:template match="/">
    <xsl:for-each select="GCC_XML/Function">
<xsl:sort select="@name"/>
      <!--xsl:if test="not(@mangled != '')"-->
      <xsl:if test="not(@attributes != '')">
      <xsl:text>extern const char nm_</xsl:text>
<xsl:value-of select="@name"/>
      <xsl:text>[] = "</xsl:text>
<xsl:value-of select="@name"/>
      <xsl:text>";
</xsl:text>
</xsl:if>
    </xsl:for-each>
  </xsl:template>
</xsl:stylesheet>
