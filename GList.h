
#ifndef GLIST_H
#define GLIST_H 1


#include <vector>

template <class T>
class GList
{
 public:
  GList()
  {

  }


  GList(GList* other)
  {
   AddAll(other);
  }

    std::vector<T> list;
    std::vector<int> flagged;



  void Add(T add, int count = 1)
  {
   for (int i = 0; i < count; i++)
   {
    list.push_back(add);
   }
  }

  void AddAt(int i, T add)
  {
   list.insert(list.begin()+i, add);
  }



  void AddAll(GList<T>* addList)
  {
   for (int i = 0; i < addList->GetSize(); i++)
   {Add((*addList)[i]);}
  }


  void Swap(int i, int j)
  {
   T hold = Get(i);
   Set(i, Get(j));
   Set(j, hold);
  }

  void Remove(int i)
  {
   list.erase(list.begin() + i);

  }

  void RemoveAll()
  {
   while (GetSize() > 0)
   {
    Remove(0);
   }
  }

  int GetSize()
  {
   return list.size();
  }

  int FindElement(T e)
  {
    for (int i = 0; i < GetSize(); i++)
   {
    if (Get(i) == e){return i;}
   }

   return -1;
  }

  T Get(int i)
  {
   return list[i];
  }

  void Set(int pos, T element)
  {
	 // list[pos] = element;
      list.insert(list.begin()+pos, element);
      list.erase(list.begin()+pos+1);
  }

  T operator[]( int i )
  {
   return Get(i);
  }

  T GetLast()
  {
   return list[GetSize()-1];
  }




  void FlagRemove(T element)
  {
   for (int i = 0; i < GetSize(); i++)
   {
    if (Get(i) == element){flagged.push_back(i); return;}
   }
  }

  void AddAll(GList<T> oList)
  {
	  for (int i = 0; i < oList.GetSize(); i++)
	  {
		  Add(oList[i]);
	  }
  }

  void RemoveAllFlagged()
  {
   for (int i = 0; i < flagged.size(); i++)
   {
    Remove(flagged[i]);
   }
   flagged.clear();
  }

  void RemoveElement(T element)
  {
   for (int i = 0; i < GetSize(); i++)
   {
    if (Get(i) == element){Remove(i); return;}
   }
  }

  bool Contains(T element)
  {
   for (int i = 0; i < GetSize(); i++)
   {
    if (Get(i) == element){return true;}
   }
   return false;
  }



  T GetRandom()
  {
   int i = (int)(rand()%GetSize());
   return Get(i);
  }






};


#endif
