# New ports collection makefile for:   Agender
# Date created:        18 December 2010
# Whom:                virtuosonic
#
# $FreeBSD$
#

PORTNAME=      Agender
PORTVERSION=      1.1.9
USE_BZIP2=    yes
CATEGORIES=    deskutils misc
MASTER_SITES=  SF/agender

MAINTAINER=    virtuosonic@users.sourceforge.net
COMMENT=       A cross-platform schedule tool

USE_WX=    2.8
WANT_UNICODE=    yes
WX_CONF_ARGS=    absolute
GNU_CONFIGURE=   yes

.if defined(WITHOUT_NLS)
PLIST_SUB+=             NLS="@comment "
.else
PLIST_SUB+=             NLS=""
.endif

.include <bsd.port.mk>
