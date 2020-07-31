#include "StickerSheet.h"

using namespace cs225;

StickerSheet::StickerSheet(const Image &picture, unsigned max)
//:max_(max)
:stickers_(new Image*[max]),
 x(new int*[max]),
 y(new int*[max])
  
{
  max_   = max;
  base_  = new Image(picture);
  sheet_ = new Image(picture);

  for(unsigned i=0;i<max_;i++){
    stickers_[i] = new Image();
            x[i] = new int(0);
            y[i] = new int(0);
  }
}


void StickerSheet::halt_(){

  for(unsigned i=0; i<max_; i++){
    if(stickers_[i]!=nullptr)
      delete stickers_[i];
      delete x[i];
      delete y[i];
  }

  if(stickers_!=nullptr)
    delete[] stickers_;

  if(base_ != nullptr)
    delete base_;

  if(x!= nullptr)
    delete[] x;

  if(y!= nullptr)
    delete[] y;

  if(sheet_!= nullptr)
    delete sheet_;

}

void StickerSheet::copy_(const StickerSheet &other){

  max_   = other.max_;
  base_  = new Image(*other.base_);
  sheet_ = new Image(*other.sheet_);
  stickers_ = new Image*[other.max_];
  x = new int*[other.max_];
  y = new int*[other.max_];

  for(unsigned i=0; i<other.max_; i++){
    stickers_[i] = new Image(*other.stickers_[i]);
            x[i] = new int(*other.x[i]);
            y[i] = new int(*other.y[i]);
  }

}


StickerSheet::~StickerSheet(){
  halt_();
}


/*
StickerSheet::StickerSheet(const StickerSheet &other):
max_(other.max_), base_(new Image(*other.base_)),stickers_(new Image*[other.max_]) 
{
  for(unsigned i=0; i<other.max_; i++){
    stickers_[i] = new Image(*other.stickers_[i]);
  }

}
*/

StickerSheet::StickerSheet(const StickerSheet &other){
  copy_(other);
}

const StickerSheet& StickerSheet::operator = (const StickerSheet &other){

  this->halt_();
  this->copy_(other);
  return *this;
}


void StickerSheet::changeMaxStickers(unsigned max){

  Image** stickers_new = new Image*[max];
  int** x_new = new int*[max];
  int** y_new = new int*[max];
  
  unsigned upper_bound = max < max_ ? max : max_;
  for(unsigned i=0; i<upper_bound; i++){
    stickers_new[i] = new Image(*stickers_[i]);
    x_new[i] = new int(*x[i]);
    y_new[i] = new int(*y[i]);
  }

  for(unsigned i=upper_bound;i<max;i++){
    stickers_new[i] = new Image();
    x_new[i] = new int(0);
    y_new[i] = new int(0);
  }

  for(unsigned i=0;i<max_;i++){
    delete stickers_[i];
    delete x[i];
    delete y[i];
  }

  delete[] stickers_;
  delete[] x; 
  delete[] y; 
 
  stickers_ = new Image*[max];
  x = new int*[max];
  y = new int*[max];

  for(unsigned i=0;i<max;i++){
    stickers_[i] = new Image(*stickers_new[i]);
    x[i] = new int(*x_new[i]);
    y[i] = new int(*y_new[i]);
    delete stickers_new[i];
    delete x_new[i];
    delete y_new[i];
  }

  delete[] stickers_new;  
  delete[] x_new;  
  delete[] y_new;  

  max_ = max;

}


/*
void StickerSheet::changeMaxStickers(unsigned max){

  Image tmp(*(this->base_));
  StickerSheet newSheet(tmp,max);

  unsigned upper_bound = max < max_ ? max : max_;

  for(unsigned i=0; i<upper_bound; i++){
    Image* tmp_stickers = newSheet.stickers_[i];
    int* tmp_x = x[i];
    int* tmp_y = y[i];
    newSheet.stickers_[i] = new Image(*stickers_[i]);  
    newSheet.x[i]         = new int(*x[i]);  
    newSheet.y[i]         = new int(*y[i]);  

    delete tmp_stickers;
    delete tmp_x;
    delete tmp_y;

  }

  this->halt_();
  this->copy_(newSheet);

}
*/


int StickerSheet::getLowestIndex(){

  //get the lowest possible layer
  int index = -1;
  for(unsigned i=0;i<max_;i++){
    //defualt constructed PNG will have width==0 && height==0
    if(stickers_[i]->width()==0 && stickers_[i]->height()==0){
      index = i;
      break;
    }
  }

  return index;

}

Image* StickerSheet::getSticker( unsigned index){

  if(index>=max_ || index<0)  return nullptr;
  else if(stickers_[index]->width()==0 || stickers_[index]->height()==0)
    return NULL;
  else 
    return stickers_[index];

}


//void StickerSheet::draw(Image& sticker,unsigned x, unsigned y){
void StickerSheet::draw(int index){

  unsigned mx = *(x[index]); 
  unsigned my = *(y[index]); 
  const Image sticker = *(stickers_[index]); 
  for(unsigned w=0; w<sticker.width(); w++){
    for(unsigned h=0; h<sticker.height(); h++){
      //HSLAPixel &mp = base_->getPixel(x+w,y+h);
      HSLAPixel &mp = sheet_->getPixel(mx+w,my+h);
      if(sticker.getPixel(w,h).a != 0. )
        mp = sticker.getPixel(w,h);
    }//end of h
  }//end of w

}


int StickerSheet::addSticker(Image& sticker, unsigned newx, unsigned newy){

  int index = getLowestIndex(); 
  if(index==-1)
    return index;

  Image *added = new Image(sticker);
  Image* tmp = stickers_[index];
  stickers_[index] = added;   
  delete tmp;
  int& mx = *x[index];
  mx = newx;
  int& my = *y[index];
  my = newy;

  //draw(sticker,x,y);
  //draw(index);

/*
  for(unsigned w=0; w<sticker.width(); w++){
    for(unsigned h=0; h<sticker.height(); h++){
      HSLAPixel &mp = base_->getPixel(x+w,y+h);
      mp = sticker.getPixel(w,h);
    }//end of h
  }//end of w
*/
  return index;
}

bool StickerSheet::translate( unsigned index, unsigned mx, unsigned my){

  Image* ptr = getSticker(index);
  if(ptr == nullptr) return false;  
  //does not contain a sticker
  if(ptr->width()==0 || ptr->height()==0) return false;
  //invalid index
  if(index>=max_) return false;

  *x[index] = mx;
  *y[index] = my; 
  return true;
}

void StickerSheet::removeSticker(unsigned index){

  Image* tmp = stickers_[index];
  stickers_[index] = new Image(); 
  delete tmp;
  *x[index] = 0; 
  *y[index] = 0; 

}


Image StickerSheet::render(){
  
  Image* tmp = sheet_;
  //reset sheet_
  sheet_ = new Image(*base_); 
  delete tmp;

  unsigned max_width = 0;
  unsigned max_height = 0;

  for(unsigned index=0; index<max_; index++){
    if(stickers_[index]==nullptr) continue;
    if(stickers_[index]->width()==0 || stickers_[index]->height()==0) continue;
    //draw(index);

    //re-scale the base in case stickers go beyond the edge
    unsigned width = stickers_[index]->width();
    unsigned height = stickers_[index]->height();
    width += *x[index];
    height += *y[index];

    if(width > max_width)
      max_width = width;
    if(height> max_height)
      max_height= height;
  } 

  unsigned new_width  = max_width > sheet_->width() ? max_width : sheet_->width();
  unsigned new_height = max_height > sheet_->height() ? max_height : sheet_->height();

  if(new_width > sheet_->width() || new_height > sheet_->height()){
    std::cout << "resize : " << std::endl;
    sheet_->resize(new_width,new_height);
    std::cout << "new width: " << sheet_->width() << std::endl;
    std::cout << "new height: " << sheet_->height() << std::endl;
  }

  for(unsigned index=0; index<max_; index++){
    if(stickers_[index]==nullptr) continue;
    if(stickers_[index]->width()==0 || stickers_[index]->height()==0) continue;
    draw(index);
  }

  sheet_->writeToFile("myImage.png");
  return *sheet_;

}

void StickerSheet::debug(){

  for(unsigned i=0; i<max_; i++){
    std::cout << *x[i] << std::endl;
  }
}




