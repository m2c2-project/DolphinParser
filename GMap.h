

#ifndef GMAP_H
#define GMAP_H 1

#include "GList.h"


template <class T, class R>
class GMap
{
 public:
	 GList<T> keyList;
	 GList<R> itemList;

	 void Put(T key, R item)
	 {
		 keyList.Add(key);
		 itemList.Add(item);
	 }

  void Set(T key, R item) // set value of an existing map elemnt
	 {

    int index = keyList.FindElement(key);

    if (index == -1) // no item found, just do a regular put
    {
     Put(key, item);
     return;
    }

    // item found, change value

    itemList.Set(index, item);


	 }

	 bool Get(T key, R* item)
	 {
		for (int i = 0; i < keyList.GetSize(); i++)
		{
			if (keyList[i] == key)
            {
                *item = itemList[i];
                return true;
            }
		}

         return false; // does not contain key
	 }


	  bool Contains(T key)
	 {
		for (int i = 0; i < keyList.GetSize(); i++)
		{
			if (keyList[i] == key)
            {

                return true;
            }
		}

         return false; // does not contain key
	 }

	  bool ContainsElement(R element)
	 {
		for (int i = 0; i < itemList.GetSize(); i++)
		{
			if (itemList[i] == element)
            {

                return true;
            }
		}

         return false; // does not contain item
	 }

  R Get(T key)
	 {
		for (int i = 0; i < keyList.GetSize(); i++)
		{
			if (keyList[i] == key)
            {
                return itemList[i];

            }
		}

         return NULL; // does not contain key
	 }


  R Get2(T key) // use with non pointers
	 {
	  		for (int i = 0; i < keyList.GetSize(); i++)
     {
      if (keyList[i] == key)
               {
                   return (itemList[i]);

               }
     }

     return R(); // does not contain key

	 }

	 void RemoveAll()
	 {
	  keyList.RemoveAll();
	  itemList.RemoveAll();
	 }

	 void Remove(T key)
	 {
	  for (int i = 0; i < keyList.GetSize(); i++)
     {
               if (keyList[i] == key)
               {
                   keyList.Remove(i);
                   itemList.Remove(i);
                   return;
               }
     }

	 }



	 void DeleteAll()
	 {
    for (int i = 0; i < itemList.GetSize(); i++)
		  {

                delete itemList[i];

            }
		  RemoveAll();
	 }




};



#endif
