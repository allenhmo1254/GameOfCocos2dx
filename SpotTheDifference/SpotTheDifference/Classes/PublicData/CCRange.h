//
//  CCRange.h
//  SMSDX
//
//  Created by  陈广文 on 13-2-20.
//
//

#ifndef SMSDX_CCRange_h
#define SMSDX_CCRange_h

typedef struct _CCRange {
    int location;
    int length;
}CCRange;

typedef CCRange* CCRangePointer;

static inline CCRange CCMakeRange(int loc, int len) {
    CCRange r;
    r.location = loc;
    r.length = len;
    return r;
}

#endif
