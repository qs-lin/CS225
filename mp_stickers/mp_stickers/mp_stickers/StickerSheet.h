/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

#include <iostream>
#include "Image.h"
#include "cs225/PNG.h"

namespace cs225{

  class StickerSheet{

    public:
      StickerSheet(const Image &picture, unsigned max);
      ~StickerSheet();
      StickerSheet(const StickerSheet &other);
      const StickerSheet& operator = (const StickerSheet &other);
      void changeMaxStickers(unsigned);
      int addSticker(Image& sticker, unsigned x, unsigned y);
      Image* getSticker(unsigned);      
      bool translate(unsigned,unsigned,unsigned);
      void removeSticker(unsigned);
      Image render();
      void debug();






    private:

      //helper function for rule of 3
      void halt_();
      void copy_(const StickerSheet &other);

      int getLowestIndex();
      //void draw(Image& sticker, unsigned x, unsigned y);
      void draw(int);

      unsigned max_;
      //base_: original one
      Image* base_;
      Image* sheet_;
      Image** stickers_;
      int** x;
      int** y;



  };
}

 
