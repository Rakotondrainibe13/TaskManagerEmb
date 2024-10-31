pragma Singleton
import QtQuick 2.15

QtObject {
    //Taille
    property int statusBarHeigth: 50
    property int heigthField: 30

    property int preferredHeigth: 30
    property int preferredWidth: 120

    property int heigthBarFooter: 20
    property int sizeTextStatusBar : 12
    property int sizeTextNormale : 14

    property int borderRadiusField : 3

    property int sizeTextTitle : 24

    // Couleurs de fond
    property color backgroundPrincipale: "lightgray"        // blanc
    property color backgroundSecondary: "#F5F5F5" // blanc fumé

    // Couleurs principales
    property color white: "white"
    property color primary: "#E6E6E6"
    property color secondary: "#6C8EBF"
    property color third: "#c0e0b4"
    property color textColor: "#333333"
    property color textColorBouton: "#333333"
    property color transparent: Qt.rgba(0, 0, 0, 0)

    // Couleurs d'avertissement
    property color warning: "#82B366"          // vert
    property color danger: "#FF0000"
    property color borderLine: "#666666"
    property color borderLineSecondary: "#d3d3d3"

    // font family
    property string fontHelvetica : "Helvetica"
    readonly property font defaultFont: Qt.font({
        family: fontHelvetica,
        pixelSize: 12,
        color: textColor
    })

    // Base64
    property string iconNotificationBase64: "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABgAAAAYCAYAAADgdz34AAAACXBIWXMAAAsTAAALEwEAmpwYAAABGElEQVR4nLWVu2oCQRhGD8HCKoWIkEBIr41lsLWJpE2Vl8gbCGIUNI2P4TNoEyISSJs0KWyilQTxktqRgX9hXLzMzM5+8MHuMP85xV4G7PMAzIApUCOFTAEl/Q0FzQEN4N2ARx0BL0DeF14G/g6A413IXucMLeBRBz6CfwfBxhWedYArqZ6xzrWH4MpFUPIQFF0ENQ/BvYug7SFougg+PQQftvA7D7iSVs7BM8A4geANuDglaCWAK2n9GPwJ2AYQbIHHOPwWWAeAK+kSuDEFrwHhStoxBd8pCL5MwSoFwdoUFIAq8Az0gL6cWD/ARA6VhTEc3U9kz0hmesKoCtM6l7Hfsb7Wa8Fy6CXYe4hJo79wLZlLu7J2Njvk+iaAz8HOygAAAABJRU5ErkJggg=="
    property string iconLogoutBase64: "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABgAAAAYCAYAAADgdz34AAAACXBIWXMAAAsTAAALEwEAmpwYAAAAh0lEQVR4nO3UQQ5AMBCF4f84FuysuABxb5xDhbDiBGPTldBQnYjES96y8yXTtPDnZiqgB8SzBihdgHkwXGw7FyCB+h2gARYtoLZnYmDSABY7/AgJtqIZSOzZCBh8gIzrSX2AXBuQGysaP3XJ9cnwoCtqgVXzJctJ3wOM9nddPkQ6oHABf9hnA2JwF/uifKGCAAAAAElFTkSuQmCC"
    property string iconSearchBase64: "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABgAAAAYCAYAAADgdz34AAAACXBIWXMAAAsTAAALEwEAmpwYAAABSUlEQVR4nLWUTU4CQRCFPze6cLgAM3fgNviz04UaBFZucMe1QBYqbvUAbnQhaLiASAKmktfJJDrT3dK+pNOZnlf1uqqrCn6iAfSBCTADvrTbdw/I2AKHwAewqVnvQPsvzq+BtZzcAQdAE9gFconf67/xBrE3N6MVcOHhdsRbh0bSKKXF57wsYvx5yJv0Rb4lDlPZdX3EiYiW8xgcyW7sI85EtAeNQS67Nx9xKaJVSwz2ZPf5XxEUoRHciGilGoNj2Y18xJ6I1kSh2AEeZHfpI2dq/43qOwTdmD5AHek6uRPgfCWBKyIwKM2iqeq8UHUVyrlLi1sLoBUj0lbYddN0rpsvSiKnwDC0EjM93FgluNQ+0vm+eK2SiFvPijYZTn6JMKnIsCKNyUSaclYlYvNqa+Q1Io8pBKgReU0lUCVyllLAiTwBL8C5nXwDnqmN6SjXt0IAAAAASUVORK5CYII="
    readonly property font headerFont: Qt.font({
        family: fontHelvetica,
        pixelSize: 24,
        weight: Font.Bold,
        color: textColor
    })

    readonly property font navbarFont: Qt.font({
        family: fontHelvetica,
        pixelSize: 10
    })
}


