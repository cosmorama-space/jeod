/**
 * @addtogroup Models
 * @{
 * @addtogroup Interactions
 * @{
 * @addtogroup Contact
 * @{
 *
 * @file models/interactions/contact/src/point_contact_facet_factory.cc
 * Factory that creates a PointContactFacet from a FlatPlateCircular facet and
 * a ContactParams object
 */

/************************** TRICK HEADER***************************************
PURPOSE:
    ()

Library dependencies:
   ((point_contact_facet_factory.o)
    (point_contact_facet.o)
    (utils/surface_model/flat_plate_circular.o)
    (dynamics/dyn_body/dyn_body.o)
    (contact_messages.o))


*******************************************************************************/

/* System includes */
#include <typeinfo>
#include <cstddef>

// JEOD includes
#include "utils/surface_model/include/flat_plate_circular.hh"
#include "dynamics/dyn_body/include/dyn_body.hh"
#include "utils/memory/include/jeod_alloc.hh"

// Model includes
#include "../include/point_contact_facet_factory.hh"
#include "../include/point_contact_facet.hh"
#include "../include/contact_messages.hh"
#include "../include/contact_params.hh"


//! Namespace jeod
namespace jeod {

JEOD_DECLARE_ATTRIBUTES (PointContactFacet)

/**
 * Default Constructor
 */

PointContactFacetFactory::PointContactFacetFactory (
   void)
{
   JEOD_REGISTER_CLASS(PointContactFacet);
}


/**
 * Destructor
 */

PointContactFacetFactory::~PointContactFacetFactory (
   void)
{

   // empty for now

}


/**
 * Create a PointContactFacet from a CircularFlatPlate facet and a
 * ContactParams object
 * @return The new EllipsoidContactFacet. Note that this is allocated and YOU are responsible for destroying it at the end!
 * \param[in] facet The CircularFlatPlate. This MUST be a circular flat plate or the algorithm will send a failure message
 * \param[in] params ContactParams
 */

InteractionFacet*
PointContactFacetFactory::create_facet (
   Facet* facet,
   FacetParams* params)
{
   ContactParams* contact_params = NULL;
   FlatPlateCircular* plate          = NULL;

   contact_params = dynamic_cast<ContactParams*> (params);
   plate      = dynamic_cast<FlatPlateCircular*> (facet);


   // We have tried casting the facet and params to the correct types.
   // if they were not the correct type, send out an error message
   if (contact_params == NULL) {

      MessageHandler::fail (
         __FILE__, __LINE__,
         ContactMessages::initialization_error,
         "the params supplied to "
         "PointContactFacetFactory::create_facet was not of type "
         "ContactParams, as is required");

   }
   if (plate == NULL) {

      MessageHandler::fail (
         __FILE__, __LINE__,
         ContactMessages::initialization_error,
         "the Facet supplied to "
         "PointContactFacetFactory::create_facet was not of type "
         "CircularFlatPlate, as is required");

   }

   // Create the interaction facet
   PointContactFacet* inter_facet =
      JEOD_ALLOC_CLASS_OBJECT (PointContactFacet, ());


   // Fill it out from the parameters and from the facet itself
   inter_facet->base_facet = facet;

   inter_facet->radius  = plate->radius;
   inter_facet->set_max_dimension();

   inter_facet->surface_type = contact_params;

   Vector3::copy (plate->position, inter_facet->position);
   Vector3::copy (plate->normal, inter_facet->normal);

   inter_facet->vehicle_body = facet->get_mass_body_ptr()->dyn_owner;
   if (inter_facet->vehicle_body == NULL) {

      MessageHandler::fail (
         __FILE__, __LINE__,
         ContactMessages::initialization_error,
         "mass_body_ptr contained in the facet supplied to"
         "PointContactFacetFactory::create_facet was not of type "
         "DynBody, as is required");

   }

   inter_facet->create_vehicle_point ();

   return inter_facet;

}


/**
 * PointContactFacetFactory specific implementation of this function.
 * If the Facet is of type CircularFlatPlate, returns true. False otherwise
 * @return true if facet is a FlatPlateCircular, false otherwise
 * \param[in] facet The facet to check
 */

bool
PointContactFacetFactory::is_correct_factory (
   Facet* facet)
{
   if (typeid(*facet) == typeid(FlatPlateCircular)) {
      return true;
   }
   else {
      return false;
   }

}

} // End JEOD namespace

/**
 * @}
 * @}
 * @}
 */
