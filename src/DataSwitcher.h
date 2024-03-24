/**
 * Stores array of data and updates index based on button press
*/

#ifndef DATASWITCHER_H
#define DATASWITCHER_H
#include <stddef.h>
#include <Arduino.h>
#include <bits/std_function.h>


template <typename T> 
class DataSwitcher
{
private:
  int prevButtonPin;
  int nextButtonPin;

  static bool canDebounceRead();

  void(*nextFunc)();
  void(*prevFunc)();

  static volatile unsigned long lastDebounceRead;
  static const unsigned long DEBOUNCE_DELAY=500;

  T* data;
public:
  static size_t size;
  static int *index;


  DataSwitcher(T* data, size_t size);
  void setPrevButtonPin(int prevButtonPin);
  void setNextButtonPin(int nextButtonPin);
  void setNextFunction(void(*nextFunc)());
  void setPrevFunction(void(*prevFunc)());
  void setIndex(int* index);

  static void next();
  static void prev();

  void setup();
};  


template<class T>
DataSwitcher<T>::DataSwitcher(T* data, size_t size){
  this->data = data;
  this->size = size;
}

template<class T>
bool DataSwitcher<T>::canDebounceRead(){
  if(millis() > lastDebounceRead + DEBOUNCE_DELAY){
    lastDebounceRead = millis();
    return true;
  }
  return false;
}

template <class T>
void DataSwitcher<T>::prev() {
  if(!canDebounceRead()) return;
  if(*index == 0){
    *index = size-1;
  }
  else{
    (*index)--;
  }
}

template <class T>
void DataSwitcher<T>::setIndex(int* index) {
  this->index = index;
}

template <class T>
void DataSwitcher<T>::next() {
  if(!canDebounceRead()) return;
  *index = (*index + 1)%size;
}

template <class T>
void DataSwitcher<T>::setNextFunction(void(*nextFunc)()) {
  this->nextFunc = nextFunc;
}

template <class T>
void DataSwitcher<T>::setPrevFunction(void(*prevFunc)()) {
  this->prevFunc = prevFunc;
}

template <class T>
void DataSwitcher<T>::setPrevButtonPin(int prevButtonPin) {
  this->prevButtonPin = prevButtonPin;
}

template <class T>
void DataSwitcher<T>::setNextButtonPin(int nextButtonPin) {
  this->nextButtonPin = nextButtonPin;
}

template <class T>  
void DataSwitcher<T>::setup() { 
  attachInterrupt(digitalPinToInterrupt(nextButtonPin), next, RISING);
  attachInterrupt(digitalPinToInterrupt(prevButtonPin), prev, RISING);
}

template <typename T> 
int* DataSwitcher<T>::index = nullptr;

template <typename T> 
volatile unsigned long DataSwitcher<T>::lastDebounceRead = 0;

template <typename T> 
size_t DataSwitcher<T>::size = 0;

#endif

