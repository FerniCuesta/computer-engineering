/**
 * @file imageop.cpp
 * @brief Fichero con definiciones para el resto de métodos de la clase Image
 */

#include <cstring>
#include <cassert>
#include <iostream>
#include <math.h>

#include <image.h>
#include <imageIO.h>

#include <assert.h>
// Genera una subimagen.
Image Image::Crop(int nrow, int ncol, int height, int width) const{

	//*****************************************************************************************
	// Comprobacion de prerrequisitos
	
	assert(nrow >= 0);

	assert(ncol >= 0);

	assert(nrow + height <= this->rows);

	assert(ncol + width <= this->cols);
	
	//*****************************************************************************************
	// Calculamos la subimagen

	Image subimagen(height, width); // Subimagen que vamos a devolver

	// Obtenemos los pixeles de la imagen y los introducimos en la subimagen
	for(int i = 0; i < height; i++)
		for(int j = 0; j < width; j++)
			subimagen.set_pixel(i, j, get_pixel(nrow + i, ncol + j));

    return subimagen;
}

// Hace zoom en una imagen
Image Image::Zoom2X() const {
    int zoom_rows = rows * 2 - 1;
    int zoom_cols = cols * 2 - 1;

    Image zoom(zoom_rows, zoom_cols);

   	// Insertar en la imagen a devolver los pixeles de la imagen original
	for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; ++j) {
            zoom.set_pixel(2 * i, 2 * j, get_pixel(i, j));
        }
    }

    byte valor_medio ;

    // Interpolar columnas
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols - 1; ++j) {
            valor_medio = roundf( (float)(get_pixel(i, j) + get_pixel(i, j + 1)) / 2);
            zoom.set_pixel(i * 2, j * 2 + 1, valor_medio);
        }
    }

    //Interpolacion filas
    for (int i = 0; i < rows - 1; i++) {
        for (int j = 0; j < cols; ++j) {
            valor_medio = roundf( (float)(get_pixel(i,j) + get_pixel(i+1,j))/2);
            zoom.set_pixel(i * 2 + 1, j * 2, valor_medio);
        }
    }

    //Interpolacion diagonal
    for(int i = 0; i < rows - 1; i++){
        for(int j = 0; j < cols - 1; j++){
            valor_medio = roundf( (float)(zoom.get_pixel(i*2, j*2) + zoom.get_pixel(i*2 + 2, j *2 ) + zoom.get_pixel(i * 2 + 2, j * 2 + 2) + zoom.get_pixel(i * 2 , j * 2 + 2))/4);
            zoom.set_pixel(i*2 + 1, j*2 + 1, valor_medio);
        }
    }


    return zoom;
}

// Genera un icono como reducción de una imagen.
Image Image::Subsample(int factor) const{

	//*****************************************************************************************
	// Comprobacion de prerrequisitos

	assert(factor >= 0);

	//*****************************************************************************************
	// Calculamos el icono

	int filas = rows/factor;
	int columnas = cols/factor;

	Image icono (filas, columnas);

	for (int i = 0; i < filas; i++)
		for(int j = 0; j < columnas; j++)
			icono.set_pixel(i, j, round(this->Mean(i*factor, j*factor, factor, factor))); // Con round redondeamos al entero mas proximo 


	return icono;	
}

// Calcula la media de los píxeles de una imagen entera o de un fragmento de ésta.
double Image::Mean (int i, int j, int height, int width) const{

	//*****************************************************************************************
	// Comprobacion de prerrequisitos
	
	assert(i >= 0);

	assert(j >= 0);

	assert(i + height <= rows);

	assert(j + width <= cols);

	//*****************************************************************************************
	// Calculamos las media

	double sumatorio = 0;
	double sumandos = 0;

	for(int a = 0; a < height; a++)
		for(int b = 0; b < width; b++){
			sumatorio = sumatorio + (float) get_pixel(i + a, j + b);
			sumandos++;
		}

	double media = sumatorio/sumandos;

	return media;
}


// Ajusta el contraste de una imagen
void Image::AdjustContrast(byte in1, byte in2, byte out1, byte out2){

	//*****************************************************************************************
	// Comprobación de prerrequisitos

	assert (0 <= in1 && in1 <= 255);

	assert (0 <= in2 && in2 <= 255);

	assert (0 <= out1 && out1 <= 255);

	assert (0 <= out2 && out2 <= 255);

	assert (in1 < in2);

	assert (out1 < out2);

	double  a = 0,
			b = 0,
			min = 0,
			max = 0, 
			parte_constante = 0,
			valor = 0,
			z = 0;

	for(int i = 0; i < size(); i++){

		z = (float) get_pixel(i);

	//Si el umbral esta entre 0 y e1
		if(0 <= z && z<=in1){
			a = 0;
			b = in1;
			min = 0;
			max = out1;
		}
		
	//Si el umbral esta entre e1 y e2
		else if(in1 <= z && z <= in2){
			a = in1;
			b = in2;
			min = out1;
			max = out2;

		}

	//Si el umbral esta entre e2 y 255
		else{
			a = in2;
			b = 255;
			min = out2;
			max = 255;
		} 

		parte_constante = (max - min) / (b - a);
		valor = roundf( (float) min + (parte_constante * (z - a)) );

		set_pixel(i, valor);
	}
}

// Original 
void Image::ShuffleRows() {
	const int p = 9973;
	Image temp(rows, cols);
	int newr;

	for (int r = 0; r < rows; r++) {
		newr = r * p % rows;
		for (int c = 0; c < cols; c++) 
			temp.set_pixel(r, c, get_pixel(newr, c));
	}
	Copy(temp);
}

/*
// Cambio de implementacion
void Image::ShuffleRows(){

	byte ** aux;
	aux = new byte * [rows];
	const int p=9973;
	int newr;

		for(int i=0; i<rows; i++){
			newr=i*p % rows;
			aux[i] = img[newr];
		}
		delete [] img;
		img=aux;

}*/