#ifndef __POWERUPS_H__
#define __POWERUPS_H__

#include "g_local.h"
#include "inventoryitem.h"

class EXPORT_FROM_DLL ScubaGear : public InventoryItem
	{
	public:
      CLASS_PROTOTYPE( ScubaGear );
                  ScubaGear();
   };

class EXPORT_FROM_DLL Adrenaline : public InventoryItem
	{
   private:
      float             health_delta;
	public:
      CLASS_PROTOTYPE( Adrenaline );
                        
                        Adrenaline();
      virtual void      Use( Event *ev );
      void              Powerdown( Event *ev );
	   virtual void      Archive( Archiver &arc );
      virtual void      Unarchive( Archiver &arc );
	};

inline EXPORT_FROM_DLL void Adrenaline::Archive
	(
	Archiver &arc
	)
   {
   InventoryItem::Archive( arc );

   arc.WriteFloat( health_delta );
   }

inline EXPORT_FROM_DLL void Adrenaline::Unarchive
	(
	Archiver &arc
	)
   {
   InventoryItem::Unarchive( arc );

   arc.ReadFloat( &health_delta );
   }

class EXPORT_FROM_DLL Cloak : public InventoryItem
	{
	public:
      CLASS_PROTOTYPE( Cloak );
                        
                        Cloak();
      virtual void      Use( Event *ev );
      void              Powerdown( Event *ev );
	};

class EXPORT_FROM_DLL Medkit : public Entity
	{
	public:
      CLASS_PROTOTYPE( Medkit );
                        
                        Medkit();
      virtual void      Use( Event *ev );
	};


class EXPORT_FROM_DLL Mutagen : public InventoryItem
	{
	public:
      CLASS_PROTOTYPE( Mutagen );
                        
                        Mutagen();
      virtual void      Use( Event *ev );
      void              Powerdown( Event *ev );
	};

class EXPORT_FROM_DLL Oxygen : public InventoryItem
	{
	public:
      CLASS_PROTOTYPE( Oxygen );
                        
                        Oxygen();
      virtual void      Use( Event *ev );
      virtual void      Pickup( Event *ev );
      void              Powerdown( Event *ev );
	};

#endif /* powerups.h */