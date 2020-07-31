#include "Image.h"
#include "StickerSheet.h"

using namespace cs225;

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  Image alma;
  Image i;
  alma.readFromFile("tests/alma.png");
  i.readFromFile("tests/i.png");
  //mySheet.changeMaxStickers(5);

  StickerSheet sheet(alma, 100);
  sheet.addSticker(i, 20, 2000);
  //mySheet.addSticker(sticker,90,90);

  sheet.render();   



  return 0;
}

