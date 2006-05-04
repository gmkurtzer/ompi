/*
 * Copyright (c) 2004-2005 The Trustees of Indiana University and Indiana
 *                         University Research and Technology
 *                         Corporation.  All rights reserved.
 * Copyright (c) 2004-2005 The University of Tennessee and The University
 *                         of Tennessee Research Foundation.  All rights
 *                         reserved.
 * Copyright (c) 2004-2005 High Performance Computing Center Stuttgart, 
 *                         University of Stuttgart.  All rights reserved.
 * Copyright (c) 2004-2005 The Regents of the University of California.
 *                         All rights reserved.
 * $COPYRIGHT$
 * 
 * Additional copyrights may follow
 * 
 * $HEADER$
 */

#ifndef OMPI_SEQ_TRACKER_H
#define OMPI_SEQ_TRACKER_H

#include "ompi_config.h"
#include "opal/class/opal_list.h"
#include "opal/threads/threads.h"
#include "opal/threads/condition.h"
#include "ompi/constants.h"
#include "ompi/mca/mpool/mpool.h"

#if defined(c_plusplus) || defined(__cplusplus)
extern "C" {
#endif

struct ompi_seq_tracker_range_t{ 
    opal_list_item_t super; 
    uint32_t seq_id_high;
    uint32_t seq_id_low;
}; 
typedef struct ompi_seq_tracker_range_t ompi_seq_tracker_range_t;

OMPI_DECLSPEC OBJ_CLASS_DECLARATION(ompi_seq_tracker_range_t);

struct ompi_seq_tracker_t{ 
    opal_list_t seq_ids;         /**< list of seqs id's that have been seen */
    ompi_seq_tracker_range_t* seq_ids_current; /**< a pointer to the last place we were in the list */

}; 
typedef struct ompi_seq_tracker_t ompi_seq_tracker_t; 

OMPI_DECLSPEC OBJ_CLASS_DECLARATION(ompi_seq_tracker_t);


/**
 *  Look for duplicate sequence number in current range.
 *  Must be called w/ matching lock held.
 */

bool ompi_seq_tracker_check_duplicate(
    ompi_seq_tracker_t* seq_tracker, 
    uint32_t seq_id);


/*
 * insert item into sequence tracking list,
 *   compacts continuous regions into a single entry
 */
void ompi_seq_tracker_insert(ompi_seq_tracker_t* seq_tracker, uint32_t seq_i);

/*
 * Copy state from one sequence tracker list into another.
 */
void ompi_seq_tracker_copy(ompi_seq_tracker_t* dst, ompi_seq_tracker_t* src);

#if defined(c_plusplus) || defined(__cplusplus)
}
#endif
#endif 

