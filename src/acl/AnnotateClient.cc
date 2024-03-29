/*
 * Copyright (C) 1996-2023 The Squid Software Foundation and contributors
 *
 * Squid software is distributed under GPLv2+ license and includes
 * contributions from numerous individuals and organizations.
 * Please see the COPYING and CONTRIBUTORS files for details.
 */

#include "squid.h"
#include "acl/AnnotateClient.h"
#include "acl/AnnotationData.h"
#include "acl/FilledChecklist.h"
#include "client_side.h"
#include "http/Stream.h"

int
Acl::AnnotateClientCheck::match(ACLChecklist * const ch)
{
    const auto checklist = Filled(ch);

    if (const auto conn = checklist->conn()) {
        const auto tdata = dynamic_cast<ACLAnnotationData*>(data.get());
        assert(tdata);
        tdata->annotate(conn->notes(), &delimiters.value, checklist->al);
        if (const auto request = checklist->request)
            tdata->annotate(request->notes(), &delimiters.value, checklist->al);
        return 1;
    }
    return 0;
}

