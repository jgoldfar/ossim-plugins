//**************************************************************************************************
//
//     OSSIM Open Source Geospatial Data Processing Library
//     See top level LICENSE.txt file for license information
//
//**************************************************************************************************

#ifndef ossimPotraceUtility_HEADER
#define ossimPotraceUtility_HEADER 1

#include <ossim/util/ossimChipProcUtil.h>
#include <ossim/plugin/ossimPluginConstants.h>
#include <ossim/imaging/ossimImageHandler.h>

extern "C" {
#include "potracelib.h"
}

class OSSIM_DLL ossimPotraceUtil : public ossimChipProcUtil
{
public:
   static const char* DESCRIPTION;
   enum OutputMode { POLYGON, LINESTRING };

   ossimPotraceUtil();

   virtual ~ossimPotraceUtil();

   virtual void setUsage(ossimArgumentParser& ap);

   virtual bool initialize(ossimArgumentParser& ap);

   virtual void initialize(const ossimKeywordlist& ap);

   virtual bool execute();

   virtual ossimString getClassName() const { return "ossimPotraceUtil"; }

   virtual void getKwlTemplate(ossimKeywordlist& kwl);

private:
   class Path
   {
   public:
      Path() : closed(true) {}
      ~Path();
      void addPotraceCurve(potrace_curve_t& curve, int segment);
      std::vector<ossimDpt> vertices;
      bool closed;
   };

   virtual void initProcessingChain();
   virtual void finalizeChain();
   potrace_bitmap_t* convertToBitmap(ossimImageSource* handler);
   bool writeGeoJSON(potrace_path_t* vectorList);
   bool pixelIsMasked(const ossimIpt& image_pt, potrace_bitmap_t* bitmap) const;
   void transformLineStrings(potrace_state_t* pathTree);
   void transformPolygons(potrace_state_t* pathTree);

   OutputMode m_mode;
   double m_alphamax;
   int m_turdSize;
   bool m_outputToConsole;
   potrace_bitmap_t* m_maskBitmap;
   potrace_bitmap_t* m_productBitmap;
};

#endif /* #ifndef ossimPotraceUtility_HEADER */
