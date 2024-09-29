/*******************************************************************************
**
** Copyright (C) 2022 ru.yewrepo.rupochta
**
** This file is part of the Отслеживание посылок Почты России project.
**
** Redistribution and use in source and binary forms,
** with or without modification, are permitted provided
** that the following conditions are met:
**
** * Redistributions of source code must retain the above copyright notice,
**   this list of conditions and the following disclaimer.
** * Redistributions in binary form must reproduce the above copyright notice,
**   this list of conditions and the following disclaimer
**   in the documentation and/or other materials provided with the distribution.
** * Neither the name of the copyright holder nor the names of its contributors
**   may be used to endorse or promote products derived from this software
**   without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
** AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
** THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
** FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
** IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
** FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
** OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
** PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
** LOSS OF USE, DATA, OR PROFITS;
** OR BUSINESS INTERRUPTION)
** HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
** WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE)
** ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
** EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
*******************************************************************************/

import QtQuick 2.0
import Sailfish.Silica 1.0
import ru.yewrepo.myparcels 1.0

CoverBackground {
    objectName: "defaultCover"

    CoverTemplate {
        id: cover
        objectName: "placeholder"
        secondaryText: getSecondaryText()
        primaryText: getPrimaryText()
    }

    function getPrimaryText(){
        var parcelCount = pageStack.currentPage.parcelsCount
        if (parcelCount !== undefined){
            if (parcelCount === 0){
                return ""
            } else {
                return parcelCount
            }
        }
    }

    function getSecondaryText(){
        var parcelCount = pageStack.currentPage.parcelsCount
        if (parcelCount !== undefined){
            if (parcelCount === 0){
                return "Нет посылок"
            } else {
                return getDeclectionWord(pageStack.currentPage.parcelsCount)
            }
        }
    }

    function getDeclectionWord(count) {
        var words = ["Посылка", "Посылки", "Посылок"];
        var n = Math.abs(count)
        n %= 100
        if (n >= 5 && n <= 20) {
            return words[2]
        }
        n %= 10;
        if (n === 1) {
            return words[0]
        }
        if (n >= 2 && n <= 4) {
            return words[1]
        }
        return words[2]
    }
}
