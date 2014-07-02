#include "Object.h"

ObjectManager::ObjectManager()
   : hOwner(NULL)
{
}
ObjectManager::~ObjectManager()
{
}

void ObjectManager::Attach(HWND hWnd)
{
   hOwner = hWnd;
}

void ObjectManager::Input(DWORD tick)
{
   std::set<Object*>::iterator it;
   for (it = depot.begin(); it != depot.end(); it++)
   {
      (*it)->Input(tick);
   }
}
void ObjectManager::Update(DWORD tick)
{
   std::set<Object*>::iterator it, jt;
   for (it = depot.begin(); it != depot.end(); it++)
   {
      (*it)->Update(tick);
   }
   for (it = depot.begin(); it != depot.end(); it++)
   {
      for (jt = it, jt++; jt != depot.end(); jt++)
      {
         if ((*it)->IsCollide(*jt))
         {
            if ((*it)->IsBreakable())
               (*it)->DoBreak();
            if ((*jt)->IsBreakable())
               (*jt)->DoBreak();
         }
      }
   }

   _clean();
}
void ObjectManager::Draw(HDC hdc)
{
   std::set<Object*>::iterator it;
   for (it = depot.begin(); it != depot.end(); it++)
   {
      (*it)->Draw(hdc);
   }
}

void ObjectManager::push(Object* obj)
{
   if (obj == NULL) return;

   depot.insert(obj);
}
void ObjectManager::pop(Object* obj)
{
   std::set<Object*>::iterator it = depot.find(obj);
   if (it == depot.end())
   {
      // do nothing...

      return;
   }

   depot.erase(it);
}
void ObjectManager::clear()
{
   std::set<Object*>::iterator it;
   for (it = depot.begin(); it != depot.end(); )
   {
      delete (*it);
      it = depot.erase(it);
   }
}

void ObjectManager::_clean()
{
   std::set<Object*>::iterator it;
   for (it = depot.begin(); it != depot.end(); )
   {
      if ((*it)->IsNeedToClean())
      {
         delete (*it);
         it = depot.erase(it);
      }
      else
      {
         it++;
      }
   }
}