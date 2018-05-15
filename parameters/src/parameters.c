/*
 * Copyright (c) 2018 Joris Vink <joris@coders.se>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <kore/kore.h>
#include <kore/http.h>

int		page(struct http_request *);

int
page(struct http_request *req)
{
	u_int16_t	id;

	if (req->method != HTTP_METHOD_GET) {
		http_response_header(req, "allow", "get");
		http_response(req, HTTP_STATUS_BAD_REQUEST, NULL, 0);
		return (KORE_RESULT_OK);
	}

	http_populate_get(req);

	if (http_argument_get_uint16(req, "id", &id)) {
		kore_log(LOG_INFO, "id: %u", id);
		http_response(req, HTTP_STATUS_OK, "ok", 2);
	} else {
		http_response(req, HTTP_STATUS_BAD_REQUEST, NULL, 0);
	}

	return (KORE_RESULT_OK);
}
