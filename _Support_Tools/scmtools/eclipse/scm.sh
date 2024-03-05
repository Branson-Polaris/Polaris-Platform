#!/bin/sh
#*******************************************************************************
# Licensed Materials - Property of IBM
# (c) Copyright IBM Corporation 2010, 2012. All Rights Reserved.
# 
# Note to U.S. Government Users Restricted Rights:  
# Use, duplication or disclosure restricted by GSA ADP Schedule 
# Contract with IBM Corp. 
#*******************************************************************************
PRGPATH="`dirname "$0"`"
export PRGPATH
exec "${PRGPATH}/../../client/eclipse/jdk/jre/bin/java" -Dorg.eclipse.emf.ecore.plugin.EcorePlugin.doNotLoadResourcesPlugin=true -Djava.protocol.handler.pkgs=com.ibm.net.ssl.www2.protocol -Dscm.show.own.errors=true -Xmx512m -Dosgi.requiredJavaVersion=1.6 -jar "${PRGPATH}/plugins/org.eclipse.equinox.launcher_1.1.1.R36x_v20101122_1400.jar" -data "@noDefault" "$@"
