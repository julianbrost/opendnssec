/*
 * Copyright (c) 2014 Jerry Lundström <lundstrom.jerry@gmail.com>
 * Copyright (c) 2014 .SE (The Internet Infrastructure Foundation).
 * Copyright (c) 2014 OpenDNSSEC AB (svb)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef __key_state_h
#define __key_state_h

#ifdef __cplusplus
extern "C" {
#endif

struct key_state;
struct key_state_list;
typedef struct key_state key_state_t;
typedef struct key_state_list key_state_list_t;

typedef enum key_state_rrstate {
    KEY_STATE_RRSTATE_INVALID = -1,
    KEY_STATE_RRSTATE_HIDDEN = 0,
    KEY_STATE_RRSTATE_RUMOURED = 1,
    KEY_STATE_RRSTATE_OMNIPRESENT = 2,
    KEY_STATE_RRSTATE_UNRETENTIVE = 3,
    KEY_STATE_RRSTATE_NA = 4
} key_state_rrstate_t;

#ifdef __cplusplus
}
#endif

#include "db_object.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A key state object.
 */
struct key_state {
    db_object_t* dbo;
    int id;
    key_state_rrstate_t state;
    int last_change;
    int minimize;
    int ttl;
};

/**
 * Create a new key state object.
 * \param[in] connection a db_connection_t pointer.
 * \return a key_state_t pointer or NULL on error.
 */
key_state_t* key_state_new(const db_connection_t* connection);

/**
 * Delete a key state object, this does not delete it from the database.
 * \param[in] key_state a key_state_t pointer.
 */
void key_state_free(key_state_t* key_state);

/**
 * Reset the content of a key state object making it as if its new. This does not
 * change anything in the database.
 * \param[in] key_state a key_state_t pointer.
 */
void key_state_reset(key_state_t* key_state);

/**
 * Copy the content of a key state object.
 * \param[in] key_state a key_state_t pointer.
 * \param[in] key_state_copy a key_state_t pointer.
 * \return DB_ERROR_* on failure, otherwise DB_OK.
 */
int key_state_copy(key_state_t* key_state, const key_state_t* key_state_copy);

/**
 * Set the content of a key state object based on a database result.
 * \param[in] key_state a key_state_t pointer.
 * \param[in] result a db_result_t pointer.
 * \return DB_ERROR_* on failure, otherwise DB_OK.
 */
int key_state_from_result(key_state_t* key_state, const db_result_t* result);

/**
 * Get the ID of a key state object. Undefined behavior if `key_state` is NULL.
 * \param[in] key_state a key_state_t pointer.
 * \return an integer.
 */
int key_state_id(const key_state_t* key_state);

/**
 * Get the RR state of a key state object.
 * \param[in] key_state a key_state_t pointer.
 * \return a key_state_rrstate_t which may be KEY_STATE_RRSTATE_INVALID on error
 * or if no RR state has been set.
 */
key_state_rrstate_t key_state_state(const key_state_t* key_state);

/**
 * Get the RR state as text of a key state object.
 * \param[in] key_state a key_state_t pointer.
 * \return a character pointer or NULL on error or if no RR state has been set.
 */
const char* key_state_state_text(const key_state_t* key_state);

/**
 * Get the last change of a key state object. Undefined behavior if `key_state`
 * is NULL.
 * \param[in] key_state a key_state_t pointer.
 * \return an integer.
 */
int key_state_last_change(const key_state_t* key_state);

/**
 * Get the minimize of a key state object. Undefined behavior if `key_state` is
 * NULL.
 * \param[in] key_state a key_state_t pointer.
 * \return an integer.
 */
int key_state_minimize(const key_state_t* key_state);

/**
 * Get the TTL of a key state object. Undefined behavior if `key_state` is NULL.
 * \param[in] key_state a key_state_t pointer.
 * \return an integer.
 */
int key_state_ttl(const key_state_t* key_state);

/**
 * Set the RR state of a key state object.
 * \param[in] key_state a key_state_t pointer.
 * \param[in] state a key_state_rrstate_t.
 * \return DB_ERROR_* on failure, otherwise DB_OK.
 */
int key_state_set_state(key_state_t* key_state, key_state_rrstate_t state);

/**
 * Set the RR state of a key state object from text.
 * \param[in] key_state a key_state_t pointer.
 * \param[in] state a character pointer.
 * \return DB_ERROR_* on failure, otherwise DB_OK.
 */
int key_state_set_state_text(key_state_t* key_state, const char* state);

/**
 * Set the last change of a key state object.
 * \param[in] key_state a key_state_t pointer.
 * \param[in] last_change an integer.
 * \return DB_ERROR_* on failure, otherwise DB_OK.
 */
int key_state_set_last_change(key_state_t* key_state, int last_change);

/**
 * Set the minimize of a key state object.
 * \param[in] key_state a key_state_t pointer.
 * \param[in] minimize an integer.
 * \return DB_ERROR_* on failure, otherwise DB_OK.
 */
int key_state_set_minimize(key_state_t* key_state, int minimize);

/**
 * Set the TTL of a key state object.
 * \param[in] key_state a key_state_t pointer.
 * \param[in] ttl an integer.
 * \return DB_ERROR_* on failure, otherwise DB_OK.
 */
int key_state_set_ttl(key_state_t* key_state, int ttl);

/**
 * Create a key state object in the database.
 * \param[in] key_state a key_state_t pointer.
 * \return DB_ERROR_* on failure, otherwise DB_OK.
 */
int key_state_create(key_state_t* key_state);

/**
 * Get a key state object from the database by an id specified in `id`.
 * \param[in] key_state a key_state_t pointer.
 * \param[in] id an integer.
 * \return DB_ERROR_* on failure, otherwise DB_OK.
 */
int key_state_get_by_id(key_state_t* key_state, int id);

/**
 * Update a key state object in the database.
 * \param[in] key_state a key_state_t pointer.
 * \return DB_ERROR_* on failure, otherwise DB_OK.
 */
int key_state_update(key_state_t* key_state);

/**
 * Delete a key state object from the database.
 * \param[in] key_state a key_state_t pointer.
 * \return DB_ERROR_* on failure, otherwise DB_OK.
 */
int key_state_delete(key_state_t* key_state);

/**
 * A list of key state objects.
 */
struct key_state_list {
    db_object_t* dbo;
    db_result_list_t* result_list;
    const db_result_t* result;
    key_state_t* key_state;
};

/**
 * Create a new key state object list.
 * \param[in] connection a db_connection_t pointer.
 * \return a key_state_list_t pointer or NULL on error.
 */
key_state_list_t* key_state_list_new(const db_connection_t* connection);

/**
 * Delete a key state object list
 * \param[in] key_state_list a key_state_list_t pointer.
 */
void key_state_list_free(key_state_list_t* key_state_list);

/**
 * Get 4 key state objects from the database.
 * \param[in] key_state_list a key_state_list_t pointer.
 * \param[in] id1 an integer.
 * \param[in] id2 an integer.
 * \param[in] id3 an integer.
 * \param[in] id4 an integer.
 * \return DB_ERROR_* on failure, otherwise DB_OK.
 */
int key_state_list_get_4_by_id(key_state_list_t* key_state_list, int id1, int id2, int id3, int id4);

/**
 * Get the first key state object in a key state object list. This will reset
 * the position of the list.
 * \param[in] key_state_list a key_state_list_t pointer.
 * \return a key_state_t pointer or NULL on error or if there are no
 * key state objects in the key state object list.
 */
const key_state_t* key_state_list_begin(key_state_list_t* key_state_list);

/**
 * Get the next key state object in a key state object list.
 * \param[in] key_state_list a key_state_list_t pointer.
 * \return a key_state_t pointer or NULL on error or if there are no more
 * key state objects in the key state object list.
 */
const key_state_t* key_state_list_next(key_state_list_t* key_state_list);

#ifdef __cplusplus
}
#endif

#endif
