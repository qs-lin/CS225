#include "Image.h"
#include "StickerSheet.h"

using namespace cs225;

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  Image alma; alma.readFromFile("tests/alma.png");
  Image i;    i.readFromFile("tests/i.png");

  StickerSheet sheet(alma, 5);


  {
    Image almaDuplicate = alma;

    StickerSheet sheetDuplicate(almaDuplicate, 5);
    sheet = sheetDuplicate;
  }

  sheet.addSticker(i, 800, 200);

  sheet.addSticker(i, 50, 500);



  sheet.changeMaxStickers(7);
  sheet.removeSticker(1);
  sheet.changeMaxStickers(4);

  //sheet.removeSticker(1);




  return 0;
}

