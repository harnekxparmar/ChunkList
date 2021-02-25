#include "ChunkList.h"


template<class T>
 ChunkList<T>::ChunkList()
{

       head=NULL;
       tail = NULL;

   
      iterNode = head;
      arrPos=-1;        

      listLen=0;        
      numChunks=0;     
 };



template<class T>
 ChunkList<T>::ChunkList(T arr[], int arrLen)
{
     if (arrLen < 0) {
         InvalidArrayLength err;
         throw err;
     }
     
     numChunks = 0;
     for (int i = 0; i < arrLen; i++)
     {
         Append(arr[i]);
     }
     iterNode = head;
     arrPos = -1;
     
}

template<class T>
 ChunkList<T>::~ChunkList()
{
     Node<T>* tmp = head;
     while (tmp != tail) {
         tmp = tmp->next;
         delete head;
         head = tmp;
     }
     delete tail;

     head = tail = NULL;
     

}

template<class T>
 void ChunkList<T>::Append(T value)
{
     if(!IsEmpty()){
         if (tail->len < 8) {
             tail->values[tail->len]=value;
             tail->len++;
             listLen++;
         }
         else if (tail->len >= 8) {
             Node<T>* newnode = new Node<T>();
             tail->next = newnode;
             tail = newnode;
             tail->values[tail->len]=value;
             tail->len++;
             numChunks++;
             listLen++;
         }
     }
     else
     {
         Node<T>* newnode = new Node<T>();
         head = tail = newnode;
         tail->next = NULL;
         tail->values[tail->len]=value;
         tail->len++;
         listLen++;
         numChunks++;
     }
}

template<class T>
 void ChunkList<T>::Remove(T value)
{
     if (!IsEmpty()) {
         Node<T>* tmp = head;
         while (tmp != NULL) {
             for (int i = 0; i < tmp->len; i++)
             {
                 if (tmp->values[i] == value) {
                     for (int j = i ; j < tmp->len-1; j++)
                     {
                         tmp->values[j] = tmp->values[j + 1];
                     }
                     tmp->len--;
                     listLen--;
                     if (tmp->len == 0) {
                         Node<T>* prev=head;
                         Node<T>* curr=head;
                         while (curr!=tmp)
                         {
                             prev = curr;
                             curr = curr->next;
                         }
                         prev->next = tmp->next;
                         delete tmp;
                         numChunks--;
                     }

                     return;
                 
                 }
                     
             }
             tmp = tmp->next;
         }
         IteratorOutOfBounds err;
         throw err;
     }
     else {
         EmptyList e;
         throw e;
         return;
     }
}

template<class T>
 int ChunkList<T>::GetLength()
{
    return listLen;
}

template<class T>
 double ChunkList<T>::LoadFactor()
{
    return listLen/(numChunks*4);
}

template<class T>
 bool ChunkList<T>::Contains(T value)
{
     if (!IsEmpty()) {
         Node<T>* tmp = head;
         while (tmp != NULL) {
             for (int i = 0; i < tmp->len; i++)
             {
                 if (tmp->values[i] == value)
                     return true;
             }
             tmp = tmp->next;
         }
         return false;
     }
     else {
         EmptyList e;
         throw e;
         return false;
     }
}

template<class T>
T ChunkList<T>::GetIndex(int i)
{

    if (!IsEmpty()) {
        if (listLen > i && i>=0) {
            int jump = i / 8;
            Node<T>* curr = head;
            for (int j = 0; j < jump; j++)
            {
                curr = curr->next;
            }
            int index = i % 8;
            return curr->values[index];
        }
        else {
            IndexOutOfBounds err;
            throw err;
        }
    }
    else {
       EmptyList e;
       throw e;
       return T();
      }
}


template<class T>
 void ChunkList<T>::ResetIterator()
{
     iterNode = head;
     arrPos = -1;
}

template<class T>
 T ChunkList<T>::GetNextItem() 
{
     arrPos++;
     if (!IsEmpty()) {
         
             if (arrPos < iterNode->len) {
                 return iterNode->values[arrPos];
             }
             else if (iterNode->next!=NULL) {
                 iterNode = iterNode->next;
                 arrPos = 0;
                 return iterNode->values[arrPos];
             }
             else {
                 IteratorOutOfBounds err;
                 throw err;
                 return NULL;
             }
                 
        
     }
     else {
         IteratorOutOfBounds err;
         throw err;
         return NULL;
     }
    
}

template<class T>
 bool ChunkList<T>::IsEmpty()
{
     if (head == NULL) {
         return true;
     }
    return false;
}
