<?xml version="1.0" encoding="UTF-8"?>
<xsl:transform version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
        <!-- varlist -->
        <xsl:template name="xslt-varlist" match="xslt-varlist">
		<xsl:param name="omit-target"/>
		<xsl:param name="with-multiple"/>
		<xsl:param name="with-optional"/>
		<xsl:param name="with-source"/>
	        <xsl:for-each select="xslt-varlist/var">
		        <xsl:if test="not($omit-target = true() and @target = true())">
	                        <xsl:copy>
		                        <xsl:copy-of select="@name"/>
			                <xsl:if test="$with-multiple = true()">
			                        <xsl:copy-of select="@multiple"/>
			        	        <xsl:if test="not(@multiple)">
			                	        <xsl:attribute name="multiple">
						        	<xsl:value-of select="../../@multiple"/>
						        </xsl:attribute>
			        	        </xsl:if>
			        	</xsl:if>
			                <xsl:if test="$with-optional = true()">
			                        <xsl:copy-of select="@optional"/>
			        	        <xsl:if test="not(@optional)">
			                	        <xsl:attribute name="optional">
						        	<xsl:value-of select="../../@optional"/>
						        </xsl:attribute>
			        	        </xsl:if>
			        	</xsl:if>
			                <xsl:if test="$with-source = true()">
			                        <xsl:copy-of select="@source"/>
			        	        <xsl:if test="not(@source)">
			        	        	<xsl:attribute name="source">
								<xsl:value-of select="../../@source"/>
							</xsl:attribute>
			        	        </xsl:if>
			                </xsl:if>
			                <xsl:if test="@target">
			                        <xsl:copy-of select="@target"/>
			                </xsl:if>
			        </xsl:copy>
		        </xsl:if>
		</xsl:for-each>
	</xsl:template>
        <!-- input -->
        <xsl:template name="xslt-input">
	        <input>
		        <xsl:attribute name="id"><xsl:value-of select="@id"/></xsl:attribute>
		        <xsl:call-template name="xslt-varlist">
				<xsl:with-param name="with-multiple" select="true()"/>
				<xsl:with-param name="with-optional" select="true()"/>
		        </xsl:call-template>
	        </input>
	</xsl:template>
        <!-- ProcForeach -->
        <xsl:template name="xslt-ProcForeach">
	        <processor name="ProcForeach">
		        <xsl:attribute name="id"><xsl:value-of select="@id"/></xsl:attribute>
	        	<input>
			        <xsl:call-template name="xslt-varlist">
					<xsl:with-param name="with-source" select="true()"/>
			        </xsl:call-template>
	        	</input>
	        	<config>
				<xsl:element name="procs">
			        	<xsl:attribute name="next">
						<xsl:value-of select="@next"/>
					</xsl:attribute>
				</xsl:element>
	        	</config>
	        	<output>
				<var name="index"/>
			        <xsl:call-template name="xslt-varlist"/>
	        	</output>
	        </processor>
	</xsl:template>
        <!-- ProcNormalize -->
        <xsl:template name="xslt-ProcNormalize">
	        <processor name="ProcNormalize">
		        <xsl:attribute name="id"><xsl:value-of select="@id"/></xsl:attribute>
	        	<input>
			        <xsl:call-template name="xslt-varlist">
					<xsl:with-param name="with-source" select="true()"/>
			        </xsl:call-template>
	        	</input>
	        	<config>
			        <xsl:for-each select="xslt-varlist/var">
					<xsl:if test="@target != true()">
					        <pdf/>
					</xsl:if>
				</xsl:for-each>
	        	</config>
	        	<output>
			        <xsl:call-template name="xslt-varlist">
					<xsl:with-param name="omit-target" select="true()"/>
			        </xsl:call-template>
	        	</output>
	        </processor>
	</xsl:template>
        <!-- ProcMatrix -->
        <xsl:template name="xslt-ProcMatrix">
	        <processor name="ProcMatrix">
		        <xsl:attribute name="id"><xsl:value-of select="@id"/></xsl:attribute>
	        	<input>
			        <xsl:call-template name="xslt-varlist">
					<xsl:with-param name="with-source" select="true()"/>
			        </xsl:call-template>
	        	</input>
	        	<config>
			        <xsl:choose>
				        <xsl:when test="@ranking = true()">
						<fill ranking="true"/>
					</xsl:when>
					<xsl:otherwise>
						<fill signal="true" background="true"/>
					</xsl:otherwise>
			        </xsl:choose>
	        	</config>
	        	<output>
			        <xsl:if test="@ranking != true()">
				        <xsl:for-each select="xslt-varlist/var">
						<xsl:if test="@target != true()">
						        <xsl:element name="var">
					                	<xsl:attribute name="name">
						        		<xsl:value-of select="concat('rot',position())"/>
						        	</xsl:attribute>
						        </xsl:element>
						</xsl:if>
					</xsl:for-each>
				</xsl:if>
	        	</output>
	        </processor>
	</xsl:template>
        <!-- ProcLikelihood -->
        <xsl:template name="xslt-ProcLikelihood">
	        <processor name="ProcLikelihood">
		        <xsl:attribute name="id"><xsl:value-of select="@id"/></xsl:attribute>
	        	<input>
			        <xsl:call-template name="xslt-varlist">
					<xsl:with-param name="with-source" select="true()"/>
			        </xsl:call-template>
	        	</input>
	        	<config>
			        <xsl:if test="@individual = true()">
					<general individual="true"/>
				</xsl:if>
			        <xsl:for-each select="xslt-varlist/var">
				        <xsl:if test="@target != true()">
					        <xsl:element name="sigbkg">
					                <xsl:if test="../../@smooth">
					                	<xsl:attribute name="smooth">
					        			<xsl:value-of select="../../@smooth"/>
					        		</xsl:attribute>
					        	</xsl:if>
					        </xsl:element>
					</xsl:if>
				</xsl:for-each>
	        	</config>
	        	<output>
			        <xsl:choose>
				        <xsl:when test="@individual = true()">
					        <xsl:call-template name="xslt-varlist">
							<xsl:with-param name="omit-target" select="true()"/>
					        </xsl:call-template>
					</xsl:when>
					<xsl:otherwise>
						<var name="discriminator"/>
					</xsl:otherwise>
			        </xsl:choose>
	        	</output>
	        </processor>
	</xsl:template>
        <!-- main template -->
        <xsl:template match="*">
	        <xsl:choose>
	                <xsl:when test="name()='xslt-input'">
	                        <xsl:call-template name="xslt-input"/>
	                </xsl:when>
	                <xsl:when test="name()='xslt-ProcForeach'">
	                        <xsl:call-template name="xslt-ProcForeach"/>
	                </xsl:when>
	                <xsl:when test="name()='xslt-ProcNormalize'">
	                        <xsl:call-template name="xslt-ProcNormalize"/>
	                </xsl:when>
	                <xsl:when test="name()='xslt-ProcMatrix'">
	                        <xsl:call-template name="xslt-ProcMatrix"/>
	                </xsl:when>
	                <xsl:when test="name()='xslt-ProcLikelihood'">
	                        <xsl:call-template name="xslt-ProcLikelihood"/>
	                </xsl:when>
	                <xsl:otherwise>
	                        <xsl:copy>
		                        <xsl:copy-of select="@*"/>
					<xsl:apply-templates/>
		                </xsl:copy>
	                </xsl:otherwise>
	        </xsl:choose>
	</xsl:template>
</xsl:transform>
