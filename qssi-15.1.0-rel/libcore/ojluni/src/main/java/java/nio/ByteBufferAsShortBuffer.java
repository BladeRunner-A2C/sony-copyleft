/*
 * Copyright (c) 2000, 2019, Oracle and/or its affiliates. All rights reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.  Oracle designates this
 * particular file as subject to the "Classpath" exception as provided
 * by Oracle in the LICENSE file that accompanied this code.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
 * or visit www.oracle.com if you need additional information or have any
 * questions.
 */

// -- This file was mechanically generated: Do not edit! -- //
// Android-note: This file is generated by ojluni/src/tools/gensrc_android.sh.

package java.nio;

import java.util.Objects;

import libcore.io.Memory;

class ByteBufferAsShortBuffer                  // package-private
    extends ShortBuffer
{



    protected final ByteBuffer bb;


    // Android-added: Added offset as address can be zero on Android.
    /**
      * The offset from the Bytebuffer at the position 0 (in addition to bb.offset) in the
      * number of bytes.
      */
    protected final int byteOffset;
    // Android-added: Merge with little- and big-endian classes.
    private final ByteOrder order;

    // Android-changed: Added ByteOrder and removed MemorySegmentProxy to be supported yet.
    ByteBufferAsShortBuffer(ByteBuffer bb,
                                     int mark, int pos, int lim, int cap,
                                     int off, ByteOrder order)
    {

        // Android-removed: Android duplicates the buffer, and merges with the read-only buffer.
        // super(mark, pos, lim, cap, segment);
        // this.bb = bb;
        // address = addr;
        // assert address >= bb.address;
        super(mark, pos, lim, cap);
        this.bb = bb.duplicate();
        this.isReadOnly = bb.isReadOnly;
        // There are only two possibilities for the type of ByteBuffer "bb", viz, DirectByteBuffer and
        // HeapByteBuffer. We only have to initialize the field when bb is an instance of
        // DirectByteBuffer.
        // The address field is used by NIOAccess#getBasePointer and GetDirectBufferAddress method
        // in art which return the address of the first usable byte of the underlying memory, i.e,
        // the position of parent buffer. Therefore, value of "off" will be equal to parent buffer's
        // position when the method is called from either HeapByteBuffer or DirectByteBuffer.
        if (bb instanceof DirectByteBuffer) {
            this.address = bb.address + off;
        }
        this.bb.order(order);
        this.order = order;
        byteOffset = off;



    }

    @Override
    Object base() {
        // Android-changed: DirectByteBuffer allocated directly assigns both hb and address field.
        // return bb.hb;
        return bb.base();
    }

    @Override
    public ShortBuffer slice() {
        int pos = this.position();
        int lim = this.limit();
        int rem = (pos <= lim ? lim - pos : 0);
        // Android-changed: Added ByteOrder and removed MemorySegmentProxy to be supported yet.
        // long addr = byteOffset(pos);
        // return new ByteBufferAsShortBuffer(bb, -1, 0, rem, rem, addr, order);
        return new ByteBufferAsShortBuffer(bb, -1, 0, rem, rem, ix(pos), order);
    }

    @Override
    public ShortBuffer slice(int index, int length) {
        Objects.checkFromIndexSize(index, length, limit());
        return new ByteBufferAsShortBuffer(bb,
                                                    -1,
                                                    0,
                                                    length,
                                                    length,
        // Android-changed: Added ByteOrder and removed MemorySegmentProxy to be supported yet.
                                                    ix(index), order);
    }

    @Override
    public ShortBuffer duplicate() {
        return new ByteBufferAsShortBuffer(bb,
                                                    this.markValue(),
                                                    this.position(),
                                                    this.limit(),
                                                    this.capacity(),
        // Android-changed: Added ByteOrder and removed MemorySegmentProxy to be supported yet.
                                                    byteOffset, order);
    }

    @Override
    public ShortBuffer asReadOnlyBuffer() {

        return new ByteBufferAsShortBuffer(bb.asReadOnlyBuffer(),
                                                 this.markValue(),
                                                 this.position(),
                                                 this.limit(),
                                                 this.capacity(),
        // Android-changed: Added ByteOrder and removed MemorySegmentProxy to be supported yet.
                                                 byteOffset, order);



    }



    private int ix(int i) {
        // Android-changed: address can be zero on Android.
        // int off = (int) (address - bb.address);
        // return (i << 1) + off;
        return (i << 1) + byteOffset;
    }

    // Android-removed: Removed unused byteOffset(long).
    /*
    protected long byteOffset(long i) {
        return (i << 1) + address;
    }
    */

    @Override
    public short get() {
        // Android-changed: Removed MemorySegmentProxy to be supported yet.
        // short x = SCOPED_MEMORY_ACCESS.getShortUnaligned(scope(), bb.hb, byteOffset(nextGetIndex()),
        //     false);
        // return (x);
        return get(nextGetIndex());
    }

    @Override
    public short get(int i) {
        // Android-changed: Removed MemorySegmentProxy to be supported yet.
        // short x = SCOPED_MEMORY_ACCESS.getShortUnaligned(scope(), bb.hb, byteOffset(checkIndex(i)),
        //    false);
        // return (x);
        return bb.getShortUnchecked(ix(checkIndex(i)));
    }

    // BEGIN Android-added: Improve the efficiency of get().
    @Override
    public ShortBuffer get(short[] dst, int off, int length) {
        Objects.checkFromIndexSize(off, length, dst.length);
        if (length > remaining())
            throw new BufferUnderflowException();
        bb.getUnchecked(ix(position), dst, off, length);
        position += length;
        return this;
    }

    @Override
    public ShortBuffer get(int index, short[] dst, int off, int length) {
        Objects.checkFromIndexSize(index, length, limit());
        Objects.checkFromIndexSize(off, length, dst.length);
        bb.getUnchecked(ix(index), dst, off, length);
        return this;
    }
    // END Android-added: Improve the efficiency of get().














    @Override
    public ShortBuffer put(short x) {

        // Android-added: Merge the Read-only buffer class with this Read-Write buffer class.
        throwIfReadOnly();
        // Android-changed: Removed MemorySegmentProxy to be supported yet.
        // short y = (x);
        // SCOPED_MEMORY_ACCESS.putShortUnaligned(scope(), bb.hb, byteOffset(nextPutIndex()), y,
        //     false);
        put(nextPutIndex(), x);
        return this;



    }

    @Override
    public ShortBuffer put(int i, short x) {

        // Android-added: Merge the Read-only buffer class with this Read-Write buffer class.
        throwIfReadOnly();
        // Android-changed: Removed MemorySegmentProxy to be supported yet.
        // short y = (x);
        // SCOPED_MEMORY_ACCESS.putShortUnaligned(scope(), bb.hb, byteOffset(checkIndex(i)), y,
        //     false);
        bb.putShortUnchecked(ix(checkIndex(i)), x);
        return this;



    }

    // BEGIN Android-added: Improve the efficiency of put(type$[]).
    @Override
    public ShortBuffer put(short[] src, int off, int length) {
        throwIfReadOnly();
        Objects.checkFromIndexSize(off, length, src.length);
        if (length > remaining())
            throw new BufferOverflowException();
        bb.putUnchecked(ix(position), src, off, length);
        position += length;
        return this;
    }

    @Override
    public ShortBuffer put(int index, short[] src, int off, int length) {
        throwIfReadOnly();
        Objects.checkFromIndexSize(index, length, limit());
        Objects.checkFromIndexSize(off, length, src.length);
        putUnchecked(index, src, off, length);
        return this;
    }

    private void putUnchecked(int index, short[] src, int off, int length) {
        bb.putUnchecked(ix(index), src, off, length);
    }

    @Override
    void putBuffer(int pos, ShortBuffer src, int srcPos, int n) {
        if (src.hb != null) {
            // this and src don't share the same backed char[].
            putUnchecked(pos, src.hb, srcPos + src.offset, n);
            return;
        }
        if (order() == src.order() &&
              src instanceof ByteBufferAsShortBuffer asSrc) { // always true if src.hb == null
            this.bb.putBuffer(ix(pos), asSrc.bb, asSrc.ix(srcPos), n << 1);
            return;
        }

        // Fallback to the slow path until memmove with bswap is implemented
        super.putBuffer(pos, src, srcPos, n);
    }
    // END Android-added: Improve the efficiency of put(type$[]).

    @Override
    public ShortBuffer compact() {

        // Android-added: Merge the Read-only buffer class with this Read-Write buffer class.
        throwIfReadOnly();
        int pos = position();
        int lim = limit();
        int rem = (pos <= lim ? lim - pos : 0);
        // Android-changed: Improve the efficiency.
        /*
        ByteBuffer db = bb.duplicate();
        db.limit(ix(lim));
        db.position(ix(0));
        ByteBuffer sb = db.slice();
        sb.position(pos << 1);
        sb.compact();
        */
        if (!(bb instanceof DirectByteBuffer)) {
            System.arraycopy(bb.array(), ix(pos), bb.array(), ix(0), rem << 1);
        } else {
            // Use pos << 1 instead of ix(pos) to avoid double counting of the offset
            // because this.address == bb.address + offset;
            Memory.memmove(this, 0, this, pos << 1, rem << 1);
        }
        position(rem);
        limit(capacity());
        discardMark();
        return this;



    }

    @Override
    public boolean isDirect() {
        return bb.isDirect();
    }

    @Override
    public boolean isReadOnly() {
        return isReadOnly;
    }











































    @Override
    public ByteOrder order() {
        return order;
    }








    // Android-added: Merge the Read-only buffer class with this Read-Write buffer class.
    private void throwIfReadOnly() {
        if (isReadOnly) {
            throw new ReadOnlyBufferException();
        }
    }
}
