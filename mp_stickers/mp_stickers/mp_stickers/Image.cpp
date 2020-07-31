#include "Image.h"

Image::Image() : cs225::PNG(){

}

Image::Image(PNG const & copy) : cs225::PNG(copy){

}

void Image::lighten(){

  for(unsigned int y=0; y<this->height(); y++){
    for(unsigned int x=0; x<this->width(); x++){
      cs225::HSLAPixel& mp = this->getPixel(x,y); 
      mp.l += 0.1;
      mp.l = mp.l > 1.0 ? 1. : mp.l; 
    }
  }  
}

void Image::lighten(double amount){

  for(unsigned int y=0; y<this->height(); y++){
    for(unsigned int x=0; x<this->width(); x++){
      cs225::HSLAPixel& mp = this->getPixel(x,y);
      mp.l += amount; 
      mp.l = mp.l > 1.0 ? 1. : mp.l;
    }
  }
}


void Image::darken(){

  for(unsigned int y=0; y<this->height(); y++){
    for(unsigned int x=0; x<this->width(); x++){
      cs225::HSLAPixel& mp = this->getPixel(x,y);
      mp.l -= 0.1;
      mp.l = mp.l < 0.0 ? 0. : mp.l;
    }
  }
}

void Image::darken(double amount){

  for(unsigned int y=0; y<this->height(); y++){
    for(unsigned int x=0; x<this->width(); x++){
      cs225::HSLAPixel& mp = this->getPixel(x,y);
      mp.l -= amount;
      mp.l = mp.l < 0.0 ? 0. : mp.l;
    }
  }
}

void Image::saturate(){

  for(unsigned int y=0; y<this->height(); y++){
    for(unsigned int x=0; x<this->width(); x++){
      cs225::HSLAPixel& mp = this->getPixel(x,y);
      mp.s += 0.1;
      mp.s = mp.s > 1.0 ? 1. : mp.s;
    }
  }
}

void Image::saturate(double amount){

  for(unsigned int y=0; y<this->height(); y++){
    for(unsigned int x=0; x<this->width(); x++){
      cs225::HSLAPixel& mp = this->getPixel(x,y);
      mp.s += amount;
      mp.s = mp.s > 1.0 ? 1. : mp.s;
    }
  }
}

void Image::desaturate(){

  for(unsigned int y=0; y<this->height(); y++){
    for(unsigned int x=0; x<this->width(); x++){
      cs225::HSLAPixel& mp = this->getPixel(x,y);
      mp.s -= 0.1;
      mp.s = mp.s < 0.0 ? 0. : mp.s;
    }
  }
}

void Image::desaturate(double amount){

  for(unsigned int y=0; y<this->height(); y++){
    for(unsigned int x=0; x<this->width(); x++){
      cs225::HSLAPixel& mp = this->getPixel(x,y);
      mp.s -= amount;
      mp.s = mp.s < 0.0 ? 0. : mp.s;
    }
  }
}

void Image::greyscale(){

  for(unsigned int y=0; y<this->height(); y++){
    for(unsigned int x=0; x<this->width(); x++){
      cs225::HSLAPixel& mp = this->getPixel(x,y);
      mp.s = 0.; 
    }
  }
}


void Image::illinify(){

  for(unsigned int y=0; y<this->height(); y++){
    for(unsigned int x=0; x<this->width(); x++){
      cs225::HSLAPixel& pixel = this->getPixel(x,y);
      if(pixel.h <=113.5 || pixel.h >=293.5) {
        pixel.h = 11;
      } else {
        pixel.h = 216;
      }
    }
  }
}


void Image::scale(double factor){

  if(factor==1.)
    return;
  else if(factor>1.)
    _large(factor);
  else
    _small(factor);
    
/*
  unsigned width = this->width();
  unsigned height = this->height();

  width = static_cast<unsigned>(factor*width);
  height= static_cast<unsigned>(factor*height);

  cs225::HSLAPixel *newImageData = new cs225::HSLAPixel[witdh*height]; 
  for(unsigned x=0; x<width_; x++){
    for(unsigned y=0; y<height_; y++){
    }
  } 

  //this->resize(width,height);
*/

}

void Image::_small(double factor){

  unsigned width = this->width();
  unsigned height = this->height();

  width = static_cast<unsigned>(factor*width);
  height= static_cast<unsigned>(factor*height);

  PNG copyPNG(*this);
  this->resize(width,height);

  int interval = static_cast<unsigned>(1/factor);

  for(unsigned int x=0; x<this->width(); x++){
    for(unsigned int y=0; y<this->height(); y++){
      cs225::HSLAPixel &mp = this->getPixel(x,y);
      mp = copyPNG.getPixel(x*interval,y*interval);
    } 
  }

} 

void Image::_large(double factor){


  unsigned width = this->width();
  unsigned height = this->height();

  width = static_cast<unsigned>(factor*width);
  height= static_cast<unsigned>(factor*height);
 
  //unsigned index = 0;
  unsigned prev_w = 0;
  unsigned prev_h = 0;
  unsigned curr_w = 0;
  unsigned curr_h = 0;

  //PNG* newPNG = new PNG(width,height);
  //copy the original PNG
  PNG copyPNG(*this); 

/*
  for(unsigned int x=0; x<this->width(); x++){
    for(unsigned int y=0; y<this->height(); y++){

      curr_w = static_cast<unsigned>((x+1)*factor);
      curr_h = static_cast<unsigned>((y+1)*factor);
    
      for(unsigned i=prev_w; i<curr_w; i++){
        for(unsigned j=prev_h; j<curr_h; j++){
          cs225::HSLAPixel &mp = newPNG->getPixel(i,j);
          mp = this->getPixel(x,y);
        }
      }//end of assignement
      prev_h = curr_h; 
    }//end of height_
    prev_w = curr_w;

  }//end of width_
*/  
  this->resize(width,height);

  for(unsigned int x=0; x<copyPNG.width(); x++){
    for(unsigned int y=0; y<copyPNG.height(); y++){

      curr_w = static_cast<unsigned>((x+1)*factor);
      curr_h = static_cast<unsigned>((y+1)*factor);

      for(unsigned i=prev_w; i<curr_w; i++){
        for(unsigned j=prev_h; j<curr_h; j++){
          cs225::HSLAPixel &mp = this->getPixel(i,j);
          mp = copyPNG.getPixel(x,y);
        }
      }//end of assignement
      prev_h = curr_h;
    }//end of height_
    prev_w = curr_w;

  }//end of width_
  
  //this->_copy(newPNG);
/*
  PNG* tmp = this;
  this = newPNG; 
  delete tmp;
  //this->resize(width,height);
*/
}

void Image::scale(unsigned width, unsigned height){

  double factor = 1.;
  if( (width/height) > ((this->width())/(this->height())) ){
    factor = static_cast<double>(width)/static_cast<double>(this->width());
  }else{
    factor = static_cast<double>(height)/static_cast<double>(this->height());
  }

  scale(factor); 

}

void Image::rotateColor( double degrees){

  for(unsigned int y=0; y<this->height(); y++){
    for(unsigned int x=0; x<this->width(); x++){
      cs225::HSLAPixel& mp = this->getPixel(x,y);
      mp.h += degrees;
      
      //if degrees > 360, (degree too large) 
      while(mp.h>360.){
        mp.h -= 360.;
      }

      //if degrees is negative
      while(mp.h<0){
        mp.h += 360.;
      }

    }
  }
}





