# make -C rountrip test
XSLTENGINE := xsltproc --nonet

WORDMLXML := /tmp/my-word.xml
WORDNORM  := /tmp/my-word.norm
WORDSECTS := /tmp/my-word.sects
WORDBLKS  := /tmp/my-word.blks
DBKXML    := /tmp/my-docbook.xml

default_target: test
.PHONY : test

test:
	$(XSLTENGINE) -o $(WORDMLXML) --stringparam wordml.template template.xml dbk2wordml.xsl specifications.xml
	$(XSLTENGINE) -o $(WORDNORM)  wordml2normalise.xsl   $(WORDMLXML)
	$(XSLTENGINE) -o $(WORDSECTS) normalise2sections.xsl $(WORDNORM)
	$(XSLTENGINE) -o $(WORDBLKS)  sections2blocks.xsl    $(WORDSECTS)
	$(XSLTENGINE) -o $(DBKXML)    blocks2dbk.xsl 			   $(WORDBLKS)
