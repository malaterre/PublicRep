#ifndef OPENVDB_TREE_LEAFNODE_HAS_BEEN_INCLUDED
#define OPENVDB_TREE_LEAFNODE_HAS_BEEN_INCLUDED

#include <Types.h>
#include <iostream>
#include <memory>
#include <string>
#include <type_traits>


namespace openvdb {
OPENVDB_USE_VERSION_NAMESPACE
namespace OPENVDB_VERSION_NAME {
namespace tree {



template<typename T, Index Log2Dim>
class LeafNode
{
public:
    using BuildType = T;
    using ValueType = T;
    using LeafNodeType = LeafNode<ValueType, Log2Dim>;
    using Ptr = SharedPtr<LeafNode>;

    static const Index
        LOG2DIM     = Log2Dim,      // needed by parent nodes
        TOTAL       = Log2Dim,      // needed by parent nodes
        DIM         = 1 << TOTAL,   // dimension along one coordinate direction
        NUM_VALUES  = 1 << 3 * Log2Dim,
        NUM_VOXELS  = NUM_VALUES,   // total number of voxels represented by this node
        SIZE        = NUM_VALUES,
        LEVEL       = 0;            // level 0 = leaf

    /// Append the Log2Dim of this LeafNode to the specified vector
    static void getNodeLog2Dims(std::vector<Index>& dims) { dims.push_back(Log2Dim); }

}; // end of LeafNode class

#if 0

////////////////////////////////////////


//@{
/// Helper metafunction used to implement LeafNode::SameConfiguration
/// (which, as an inner class, can't be independently specialized)
template<Index Dim1, typename NodeT2>
struct SameLeafConfig { static const bool value = false; };

template<Index Dim1, typename T2>
struct SameLeafConfig<Dim1, LeafNode<T2, Dim1> > { static const bool value = true; };
//@}


////////////////////////////////////////


template<typename T, Index Log2Dim>
inline
LeafNode<T, Log2Dim>::LeafNode():
    mValueMask(),//default is off!
    mOrigin(0, 0, 0)
{
}


template<typename T, Index Log2Dim>
inline
LeafNode<T, Log2Dim>::LeafNode(const Coord& xyz, const ValueType& val, bool active):
    mBuffer(val),
    mValueMask(active),
    mOrigin(xyz & (~(DIM - 1)))
{
}


template<typename T, Index Log2Dim>
inline
LeafNode<T, Log2Dim>::LeafNode(PartialCreate, const Coord& xyz, const ValueType& val, bool active):
    mBuffer(PartialCreate(), val),
    mValueMask(active),
    mOrigin(xyz & (~(DIM - 1)))
{
}


template<typename T, Index Log2Dim>
inline
LeafNode<T, Log2Dim>::LeafNode(const LeafNode& other):
    mBuffer(other.mBuffer),
    mValueMask(other.valueMask()),
    mOrigin(other.mOrigin)
{
}


// Copy-construct from a leaf node with the same configuration but a different ValueType.
template<typename T, Index Log2Dim>
template<typename OtherValueType>
inline
LeafNode<T, Log2Dim>::LeafNode(const LeafNode<OtherValueType, Log2Dim>& other):
    mValueMask(other.valueMask()),
    mOrigin(other.mOrigin)
{
    struct Local {
        /// @todo Consider using a value conversion functor passed as an argument instead.
        static inline ValueType convertValue(const OtherValueType& val) { return ValueType(val); }
    };

    for (Index i = 0; i < SIZE; ++i) {
        mBuffer[i] = Local::convertValue(other.mBuffer[i]);
    }
}


template<typename T, Index Log2Dim>
template<typename OtherValueType>
inline
LeafNode<T, Log2Dim>::LeafNode(const LeafNode<OtherValueType, Log2Dim>& other,
                               const ValueType& background, TopologyCopy):
    mBuffer(background),
    mValueMask(other.valueMask()),
    mOrigin(other.mOrigin)
{
}


template<typename T, Index Log2Dim>
template<typename OtherValueType>
inline
LeafNode<T, Log2Dim>::LeafNode(const LeafNode<OtherValueType, Log2Dim>& other,
    const ValueType& offValue, const ValueType& onValue, TopologyCopy):
    mValueMask(other.valueMask()),
    mOrigin(other.mOrigin)
{
    for (Index i = 0; i < SIZE; ++i) {
        mBuffer[i] = (mValueMask.isOn(i) ? onValue : offValue);
    }
}


template<typename T, Index Log2Dim>
inline
LeafNode<T, Log2Dim>::~LeafNode()
{
}


template<typename T, Index Log2Dim>
inline std::string
LeafNode<T, Log2Dim>::str() const
{
    std::ostringstream ostr;
    ostr << "LeafNode @" << mOrigin << ": " << mBuffer;
    return ostr.str();
}


////////////////////////////////////////


template<typename T, Index Log2Dim>
inline Index
LeafNode<T, Log2Dim>::coordToOffset(const Coord& xyz)
{
    assert ((xyz[0] & (DIM-1u)) < DIM && (xyz[1] & (DIM-1u)) < DIM && (xyz[2] & (DIM-1u)) < DIM);
    return ((xyz[0] & (DIM-1u)) << 2*Log2Dim)
        +  ((xyz[1] & (DIM-1u)) <<  Log2Dim)
        +   (xyz[2] & (DIM-1u));
}

template<typename T, Index Log2Dim>
inline Coord
LeafNode<T, Log2Dim>::offsetToLocalCoord(Index n)
{
    assert(n<(1<< 3*Log2Dim));
    Coord xyz;
    xyz.setX(n >> 2*Log2Dim);
    n &= ((1<<2*Log2Dim)-1);
    xyz.setY(n >> Log2Dim);
    xyz.setZ(n & ((1<<Log2Dim)-1));
    return xyz;
}


template<typename T, Index Log2Dim>
inline Coord
LeafNode<T, Log2Dim>::offsetToGlobalCoord(Index n) const
{
    return (this->offsetToLocalCoord(n) + this->origin());
}


////////////////////////////////////////


template<typename ValueT, Index Log2Dim>
inline const ValueT&
LeafNode<ValueT, Log2Dim>::getValue(const Coord& xyz) const
{
    return this->getValue(LeafNode::coordToOffset(xyz));
}

template<typename ValueT, Index Log2Dim>
inline const ValueT&
LeafNode<ValueT, Log2Dim>::getValue(Index offset) const
{
    assert(offset < SIZE);
    return mBuffer[offset];
}


template<typename T, Index Log2Dim>
inline bool
LeafNode<T, Log2Dim>::probeValue(const Coord& xyz, ValueType& val) const
{
    return this->probeValue(LeafNode::coordToOffset(xyz), val);
}

template<typename T, Index Log2Dim>
inline bool
LeafNode<T, Log2Dim>::probeValue(Index offset, ValueType& val) const
{
    assert(offset < SIZE);
    val = mBuffer[offset];
    return mValueMask.isOn(offset);
}


template<typename T, Index Log2Dim>
inline void
LeafNode<T, Log2Dim>::setValueOff(const Coord& xyz, const ValueType& val)
{
    this->setValueOff(LeafNode::coordToOffset(xyz), val);
}

template<typename T, Index Log2Dim>
inline void
LeafNode<T, Log2Dim>::setValueOff(Index offset, const ValueType& val)
{
    assert(offset < SIZE);
    mBuffer.setValue(offset, val);
    mValueMask.setOff(offset);
}


template<typename T, Index Log2Dim>
inline void
LeafNode<T, Log2Dim>::setActiveState(const Coord& xyz, bool on)
{
    mValueMask.set(this->coordToOffset(xyz), on);
}


template<typename T, Index Log2Dim>
inline void
LeafNode<T, Log2Dim>::setValueOnly(const Coord& xyz, const ValueType& val)
{
    this->setValueOnly(LeafNode::coordToOffset(xyz), val);
}

template<typename T, Index Log2Dim>
inline void
LeafNode<T, Log2Dim>::setValueOnly(Index offset, const ValueType& val)
{
    assert(offset<SIZE); mBuffer.setValue(offset, val);
}


////////////////////////////////////////


template<typename T, Index Log2Dim>
inline void
LeafNode<T, Log2Dim>::clip(const CoordBBox& clipBBox, const T& background)
{
    CoordBBox nodeBBox = this->getNodeBoundingBox();
    if (!clipBBox.hasOverlap(nodeBBox)) {
        // This node lies completely outside the clipping region.  Fill it with the background.
        this->fill(background, /*active=*/false);
    } else if (clipBBox.isInside(nodeBBox)) {
        // This node lies completely inside the clipping region.  Leave it intact.
        return;
    }

    // This node isn't completely contained inside the clipping region.
    // Set any voxels that lie outside the region to the background value.

    // Construct a boolean mask that is on inside the clipping region and off outside it.
    NodeMaskType mask;
    nodeBBox.intersect(clipBBox);
    Coord xyz;
    int &x = xyz.x(), &y = xyz.y(), &z = xyz.z();
    for (x = nodeBBox.min().x(); x <= nodeBBox.max().x(); ++x) {
        for (y = nodeBBox.min().y(); y <= nodeBBox.max().y(); ++y) {
            for (z = nodeBBox.min().z(); z <= nodeBBox.max().z(); ++z) {
                mask.setOn(static_cast<Index32>(this->coordToOffset(xyz)));
            }
        }
    }

    // Set voxels that lie in the inactive region of the mask (i.e., outside
    // the clipping region) to the background value.
    for (MaskOffIterator maskIter = mask.beginOff(); maskIter; ++maskIter) {
        this->setValueOff(maskIter.pos(), background);
    }
}


////////////////////////////////////////


template<typename T, Index Log2Dim>
inline void
LeafNode<T, Log2Dim>::fill(const CoordBBox& bbox, const ValueType& value, bool active)
{
    if (!this->allocate()) return;

    auto clippedBBox = this->getNodeBoundingBox();
    clippedBBox.intersect(bbox);
    if (!clippedBBox) return;

    for (Int32 x = clippedBBox.min().x(); x <= clippedBBox.max().x(); ++x) {
        const Index offsetX = (x & (DIM-1u)) << 2*Log2Dim;
        for (Int32 y = clippedBBox.min().y(); y <= clippedBBox.max().y(); ++y) {
            const Index offsetXY = offsetX + ((y & (DIM-1u)) << Log2Dim);
            for (Int32 z = clippedBBox.min().z(); z <= clippedBBox.max().z(); ++z) {
                const Index offset = offsetXY + (z & (DIM-1u));
                mBuffer[offset] = value;
                mValueMask.set(offset, active);
            }
        }
    }
}

template<typename T, Index Log2Dim>
inline void
LeafNode<T, Log2Dim>::fill(const ValueType& value)
{
    mBuffer.fill(value);
}

template<typename T, Index Log2Dim>
inline void
LeafNode<T, Log2Dim>::fill(const ValueType& value, bool active)
{
    mBuffer.fill(value);
    mValueMask.set(active);
}


////////////////////////////////////////


template<typename T, Index Log2Dim>
template<typename DenseT>
inline void
LeafNode<T, Log2Dim>::copyToDense(const CoordBBox& bbox, DenseT& dense) const
{
    mBuffer.loadValues();

    using DenseValueType = typename DenseT::ValueType;

    const size_t xStride = dense.xStride(), yStride = dense.yStride(), zStride = dense.zStride();
    const Coord& min = dense.bbox().min();
    DenseValueType* t0 = dense.data() + zStride * (bbox.min()[2] - min[2]); // target array
    const T* s0 = &mBuffer[bbox.min()[2] & (DIM-1u)]; // source array
    for (Int32 x = bbox.min()[0], ex = bbox.max()[0] + 1; x < ex; ++x) {
        DenseValueType* t1 = t0 + xStride * (x - min[0]);
        const T* s1 = s0 + ((x & (DIM-1u)) << 2*Log2Dim);
        for (Int32 y = bbox.min()[1], ey = bbox.max()[1] + 1; y < ey; ++y) {
            DenseValueType* t2 = t1 + yStride * (y - min[1]);
            const T* s2 = s1 + ((y & (DIM-1u)) << Log2Dim);
            for (Int32 z = bbox.min()[2], ez = bbox.max()[2] + 1; z < ez; ++z, t2 += zStride) {
                *t2 = DenseValueType(*s2++);
            }
        }
    }
}


template<typename T, Index Log2Dim>
template<typename DenseT>
inline void
LeafNode<T, Log2Dim>::copyFromDense(const CoordBBox& bbox, const DenseT& dense,
                                    const ValueType& background, const ValueType& tolerance)
{
    if (!this->allocate()) return;

    using DenseValueType = typename DenseT::ValueType;

    const size_t xStride = dense.xStride(), yStride = dense.yStride(), zStride = dense.zStride();
    const Coord& min = dense.bbox().min();

    const DenseValueType* s0 = dense.data() + zStride * (bbox.min()[2] - min[2]); // source
    const Int32 n0 = bbox.min()[2] & (DIM-1u);
    for (Int32 x = bbox.min()[0], ex = bbox.max()[0]+1; x < ex; ++x) {
        const DenseValueType* s1 = s0 + xStride * (x - min[0]);
        const Int32 n1 = n0 + ((x & (DIM-1u)) << 2*LOG2DIM);
        for (Int32 y = bbox.min()[1], ey = bbox.max()[1]+1; y < ey; ++y) {
            const DenseValueType* s2 = s1 + yStride * (y - min[1]);
            Int32 n2 = n1 + ((y & (DIM-1u)) << LOG2DIM);
            for (Int32 z = bbox.min()[2], ez = bbox.max()[2]+1; z < ez; ++z, ++n2, s2 += zStride) {
                if (math::isApproxEqual(background, ValueType(*s2), tolerance)) {
                    mValueMask.setOff(n2);
                    mBuffer[n2] = background;
                } else {
                    mValueMask.setOn(n2);
                    mBuffer[n2] = ValueType(*s2);
                }
            }
        }
    }
}


////////////////////////////////////////


template<typename T, Index Log2Dim>
inline void
LeafNode<T, Log2Dim>::readTopology(std::istream& is, bool /*fromHalf*/)
{
    mValueMask.load(is);
}


template<typename T, Index Log2Dim>
inline void
LeafNode<T, Log2Dim>::writeTopology(std::ostream& os, bool /*toHalf*/) const
{
    mValueMask.save(os);
}


////////////////////////////////////////



template<typename T, Index Log2Dim>
inline void
LeafNode<T,Log2Dim>::skipCompressedValues(bool seekable, std::istream& is, bool fromHalf)
{
    if (seekable) {
        // Seek over voxel values.
        io::readCompressedValues<ValueType, NodeMaskType>(
            is, nullptr, SIZE, mValueMask, fromHalf);
    } else {
        // Read and discard voxel values.
        Buffer temp;
        io::readCompressedValues(is, temp.mData, SIZE, mValueMask, fromHalf);
    }
}


template<typename T, Index Log2Dim>
inline void
LeafNode<T,Log2Dim>::readBuffers(std::istream& is, bool fromHalf)
{
    this->readBuffers(is, CoordBBox::inf(), fromHalf);
}


template<typename T, Index Log2Dim>
inline void
LeafNode<T,Log2Dim>::readBuffers(std::istream& is, const CoordBBox& clipBBox, bool fromHalf)
{
    SharedPtr<io::StreamMetadata> meta = io::getStreamMetadataPtr(is);
    const bool seekable = meta && meta->seekable();

    std::streamoff maskpos = is.tellg();

    if (seekable) {
        // Seek over the value mask.
        mValueMask.seek(is);
    } else {
        // Read in the value mask.
        mValueMask.load(is);
    }

    int8_t numBuffers = 1;
    if (io::getFormatVersion(is) < OPENVDB_FILE_VERSION_NODE_MASK_COMPRESSION) {
        // Read in the origin.
        is.read(reinterpret_cast<char*>(&mOrigin), sizeof(Coord::ValueType) * 3);

        // Read in the number of buffers, which should now always be one.
        is.read(reinterpret_cast<char*>(&numBuffers), sizeof(int8_t));
    }

    CoordBBox nodeBBox = this->getNodeBoundingBox();
    if (!clipBBox.hasOverlap(nodeBBox)) {
        // This node lies completely outside the clipping region.
        skipCompressedValues(seekable, is, fromHalf);
        mValueMask.setOff();
        mBuffer.setOutOfCore(false);
    } else {
        // If this node lies completely inside the clipping region and it is being read
        // from a memory-mapped file, delay loading of its buffer until the buffer
        // is actually accessed.  (If this node requires clipping, its buffer
        // must be accessed and therefore must be loaded.)
        io::MappedFile::Ptr mappedFile = io::getMappedFilePtr(is);
        const bool delayLoad = ((mappedFile.get() != nullptr) && clipBBox.isInside(nodeBBox));

        if (delayLoad) {
            mBuffer.setOutOfCore(true);
            mBuffer.mFileInfo = new typename Buffer::FileInfo;
            mBuffer.mFileInfo->meta = meta;
            mBuffer.mFileInfo->bufpos = is.tellg();
            mBuffer.mFileInfo->mapping = mappedFile;
            // Save the offset to the value mask, because the in-memory copy
            // might change before the value buffer gets read.
            mBuffer.mFileInfo->maskpos = maskpos;
            // Skip over voxel values.
            skipCompressedValues(seekable, is, fromHalf);
        } else {
            mBuffer.allocate();
            io::readCompressedValues(is, mBuffer.mData, SIZE, mValueMask, fromHalf);
            mBuffer.setOutOfCore(false);

            // Get this tree's background value.
            T background = zeroVal<T>();
            if (const void* bgPtr = io::getGridBackgroundValuePtr(is)) {
                background = *static_cast<const T*>(bgPtr);
            }
            this->clip(clipBBox, background);
        }
    }

    if (numBuffers > 1) {
        // Read in and discard auxiliary buffers that were created with earlier
        // versions of the library.  (Auxiliary buffers are not mask compressed.)
        const bool zipped = io::getDataCompression(is) & io::COMPRESS_ZIP;
        Buffer temp;
        for (int i = 1; i < numBuffers; ++i) {
            if (fromHalf) {
                io::HalfReader<io::RealToHalf<T>::isReal, T>::read(is, temp.mData, SIZE, zipped);
            } else {
                io::readData<T>(is, temp.mData, SIZE, zipped);
            }
        }
    }

    // increment the leaf number
    if (meta)   meta->setLeaf(meta->leaf() + 1);
}


template<typename T, Index Log2Dim>
inline void
LeafNode<T, Log2Dim>::writeBuffers(std::ostream& os, bool toHalf) const
{
    // Write out the value mask.
    mValueMask.save(os);

    mBuffer.loadValues();

    io::writeCompressedValues(os, mBuffer.mData, SIZE,
        mValueMask, /*childMask=*/NodeMaskType(), toHalf);
}


////////////////////////////////////////


template<typename T, Index Log2Dim>
inline bool
LeafNode<T, Log2Dim>::operator==(const LeafNode& other) const
{
    return mOrigin == other.mOrigin &&
           mValueMask == other.valueMask() &&
           mBuffer == other.mBuffer;
}


template<typename T, Index Log2Dim>
inline Index64
LeafNode<T, Log2Dim>::memUsage() const
{
    // Use sizeof(*this) to capture alignment-related padding
    // (but note that sizeof(*this) includes sizeof(mBuffer)).
    return sizeof(*this) + mBuffer.memUsage() - sizeof(mBuffer);
}


template<typename T, Index Log2Dim>
inline void
LeafNode<T, Log2Dim>::evalActiveBoundingBox(CoordBBox& bbox, bool visitVoxels) const
{
    CoordBBox this_bbox = this->getNodeBoundingBox();
    if (bbox.isInside(this_bbox)) return;//this LeafNode is already enclosed in the bbox
    if (ValueOnCIter iter = this->cbeginValueOn()) {//any active values?
        if (visitVoxels) {//use voxel granularity?
            this_bbox.reset();
            for(; iter; ++iter) this_bbox.expand(this->offsetToLocalCoord(iter.pos()));
            this_bbox.translate(this->origin());
        }
        bbox.expand(this_bbox);
    }
}


template<typename T, Index Log2Dim>
template<typename OtherType, Index OtherLog2Dim>
inline bool
LeafNode<T, Log2Dim>::hasSameTopology(const LeafNode<OtherType, OtherLog2Dim>* other) const
{
    assert(other);
    return (Log2Dim == OtherLog2Dim && mValueMask == other->getValueMask());
}

template<typename T, Index Log2Dim>
inline bool
LeafNode<T, Log2Dim>::isConstant(ValueType& firstValue,
                                 bool& state,
                                 const ValueType& tolerance) const
{
    if (!mValueMask.isConstant(state)) return false;// early termination
    firstValue = mBuffer[0];
    for (Index i = 1; i < SIZE; ++i) {
        if ( !math::isApproxEqual(mBuffer[i], firstValue, tolerance) ) return false;// early termination
    }
    return true;
}

template<typename T, Index Log2Dim>
inline bool
LeafNode<T, Log2Dim>::isConstant(ValueType& minValue,
                                 ValueType& maxValue,
                                 bool& state,
                                 const ValueType& tolerance) const
{
    if (!mValueMask.isConstant(state)) return false;// early termination
    minValue = maxValue = mBuffer[0];
    for (Index i = 1; i < SIZE; ++i) {
        const T& v = mBuffer[i];
        if (v < minValue) {
            if ((maxValue - v) > tolerance) return false;// early termination
            minValue = v;
        } else if (v > maxValue) {
            if ((v - minValue) > tolerance) return false;// early termination
            maxValue = v;
        }
    }
    return true;
}

template<typename T, Index Log2Dim>
inline T
LeafNode<T, Log2Dim>::medianAll(T *tmp) const
{
    std::unique_ptr<T[]> data(nullptr);
    if (tmp == nullptr) {//allocate temporary storage
        data.reset(new T[NUM_VALUES]);
        tmp = data.get();
    }
    if (tmp != mBuffer.data()) {
        const T* src = mBuffer.data();
        for (T* dst = tmp; dst-tmp < NUM_VALUES;) *dst++ = *src++;
    }
    static const size_t midpoint = (NUM_VALUES - 1) >> 1;
    std::nth_element(tmp, tmp + midpoint, tmp + NUM_VALUES);
    return tmp[midpoint];
}

template<typename T, Index Log2Dim>
inline Index
LeafNode<T, Log2Dim>::medianOn(T &value, T *tmp) const
{
    const Index count = mValueMask.countOn();
    if (count == NUM_VALUES) {//special case: all voxels are active
        value = this->medianAll(tmp);
        return NUM_VALUES;
    } else if (count == 0) {
        return 0;
    }
    std::unique_ptr<T[]> data(nullptr);
    if (tmp == nullptr) {//allocate temporary storage
        data.reset(new T[count]);// 0 < count < NUM_VALUES
        tmp = data.get();
    }
    for (auto iter=this->cbeginValueOn(); iter; ++iter) *tmp++ = *iter;
    T *begin = tmp - count;
    const size_t midpoint = (count - 1) >> 1;
    std::nth_element(begin, begin + midpoint, tmp);
    value = begin[midpoint];
    return count;
}

template<typename T, Index Log2Dim>
inline Index
LeafNode<T, Log2Dim>::medianOff(T &value, T *tmp) const
{
    const Index count = mValueMask.countOff();
    if (count == NUM_VALUES) {//special case: all voxels are inactive
        value = this->medianAll(tmp);
        return NUM_VALUES;
    } else if (count == 0) {
        return 0;
    }
    std::unique_ptr<T[]> data(nullptr);
    if (tmp == nullptr) {//allocate temporary storage
        data.reset(new T[count]);// 0 < count < NUM_VALUES
        tmp = data.get();
    }
    for (auto iter=this->cbeginValueOff(); iter; ++iter) *tmp++ = *iter;
    T *begin = tmp - count;
    const size_t midpoint = (count - 1) >> 1;
    std::nth_element(begin, begin + midpoint, tmp);
    value = begin[midpoint];
    return count;
}

////////////////////////////////////////


template<typename T, Index Log2Dim>
inline void
LeafNode<T, Log2Dim>::addTile(Index /*level*/, const Coord& xyz, const ValueType& val, bool active)
{
    this->addTile(this->coordToOffset(xyz), val, active);
}

template<typename T, Index Log2Dim>
inline void
LeafNode<T, Log2Dim>::addTile(Index offset, const ValueType& val, bool active)
{
    assert(offset < SIZE);
    setValueOnly(offset, val);
    setActiveState(offset, active);
}

template<typename T, Index Log2Dim>
template<typename AccessorT>
inline void
LeafNode<T, Log2Dim>::addTileAndCache(Index level, const Coord& xyz,
    const ValueType& val, bool active, AccessorT&)
{
    this->addTile(level, xyz, val, active);
}


////////////////////////////////////////


template<typename T, Index Log2Dim>
inline void
LeafNode<T, Log2Dim>::resetBackground(const ValueType& oldBackground,
                                      const ValueType& newBackground)
{
    if (!this->allocate()) return;

    typename NodeMaskType::OffIterator iter;
    // For all inactive values...
    for (iter = this->mValueMask.beginOff(); iter; ++iter) {
        ValueType &inactiveValue = mBuffer[iter.pos()];
        if (math::isApproxEqual(inactiveValue, oldBackground)) {
            inactiveValue = newBackground;
        } else if (math::isApproxEqual(inactiveValue, math::negative(oldBackground))) {
            inactiveValue = math::negative(newBackground);
        }
    }
}


template<typename T, Index Log2Dim>
template<MergePolicy Policy>
inline void
LeafNode<T, Log2Dim>::merge(const LeafNode& other)
{
    if (!this->allocate()) return;

    OPENVDB_NO_UNREACHABLE_CODE_WARNING_BEGIN
    if (Policy == MERGE_NODES) return;
    typename NodeMaskType::OnIterator iter = other.valueMask().beginOn();
    for (; iter; ++iter) {
        const Index n = iter.pos();
        if (mValueMask.isOff(n)) {
            mBuffer[n] = other.mBuffer[n];
            mValueMask.setOn(n);
        }
    }
    OPENVDB_NO_UNREACHABLE_CODE_WARNING_END
}

template<typename T, Index Log2Dim>
template<MergePolicy Policy>
inline void
LeafNode<T, Log2Dim>::merge(const LeafNode& other,
    const ValueType& /*bg*/, const ValueType& /*otherBG*/)
{
    this->template merge<Policy>(other);
}

template<typename T, Index Log2Dim>
template<MergePolicy Policy>
inline void
LeafNode<T, Log2Dim>::merge(const ValueType& tileValue, bool tileActive)
{
    if (!this->allocate()) return;

    OPENVDB_NO_UNREACHABLE_CODE_WARNING_BEGIN
    if (Policy != MERGE_ACTIVE_STATES_AND_NODES) return;
    if (!tileActive) return;
    // Replace all inactive values with the active tile value.
    for (typename NodeMaskType::OffIterator iter = mValueMask.beginOff(); iter; ++iter) {
        const Index n = iter.pos();
        mBuffer[n] = tileValue;
        mValueMask.setOn(n);
    }
    OPENVDB_NO_UNREACHABLE_CODE_WARNING_END
}


template<typename T, Index Log2Dim>
template<typename OtherType>
inline void
LeafNode<T, Log2Dim>::topologyUnion(const LeafNode<OtherType, Log2Dim>& other, bool)
{
    mValueMask |= other.valueMask();
}

template<typename T, Index Log2Dim>
template<typename OtherType>
inline void
LeafNode<T, Log2Dim>::topologyIntersection(const LeafNode<OtherType, Log2Dim>& other,
                                           const ValueType&)
{
    mValueMask &= other.valueMask();
}

template<typename T, Index Log2Dim>
template<typename OtherType>
inline void
LeafNode<T, Log2Dim>::topologyDifference(const LeafNode<OtherType, Log2Dim>& other,
                                         const ValueType&)
{
    mValueMask &= !other.valueMask();
}

template<typename T, Index Log2Dim>
inline void
LeafNode<T, Log2Dim>::negate()
{
    if (!this->allocate()) return;

    for (Index i = 0; i < SIZE; ++i) {
        mBuffer[i] = -mBuffer[i];
    }
}


////////////////////////////////////////


template<typename T, Index Log2Dim>
template<typename CombineOp>
inline void
LeafNode<T, Log2Dim>::combine(const LeafNode& other, CombineOp& op)
{
    if (!this->allocate()) return;

    CombineArgs<T> args;
    for (Index i = 0; i < SIZE; ++i) {
        op(args.setARef(mBuffer[i])
            .setAIsActive(mValueMask.isOn(i))
            .setBRef(other.mBuffer[i])
            .setBIsActive(other.valueMask().isOn(i))
            .setResultRef(mBuffer[i]));
        mValueMask.set(i, args.resultIsActive());
    }
}


template<typename T, Index Log2Dim>
template<typename CombineOp>
inline void
LeafNode<T, Log2Dim>::combine(const ValueType& value, bool valueIsActive, CombineOp& op)
{
    if (!this->allocate()) return;

    CombineArgs<T> args;
    args.setBRef(value).setBIsActive(valueIsActive);
    for (Index i = 0; i < SIZE; ++i) {
        op(args.setARef(mBuffer[i])
            .setAIsActive(mValueMask.isOn(i))
            .setResultRef(mBuffer[i]));
        mValueMask.set(i, args.resultIsActive());
    }
}


////////////////////////////////////////


template<typename T, Index Log2Dim>
template<typename CombineOp, typename OtherType>
inline void
LeafNode<T, Log2Dim>::combine2(const LeafNode& other, const OtherType& value,
    bool valueIsActive, CombineOp& op)
{
    if (!this->allocate()) return;

    CombineArgs<T, OtherType> args;
    args.setBRef(value).setBIsActive(valueIsActive);
    for (Index i = 0; i < SIZE; ++i) {
        op(args.setARef(other.mBuffer[i])
            .setAIsActive(other.valueMask().isOn(i))
            .setResultRef(mBuffer[i]));
        mValueMask.set(i, args.resultIsActive());
    }
}


template<typename T, Index Log2Dim>
template<typename CombineOp, typename OtherNodeT>
inline void
LeafNode<T, Log2Dim>::combine2(const ValueType& value, const OtherNodeT& other,
    bool valueIsActive, CombineOp& op)
{
    if (!this->allocate()) return;

    CombineArgs<T, typename OtherNodeT::ValueType> args;
    args.setARef(value).setAIsActive(valueIsActive);
    for (Index i = 0; i < SIZE; ++i) {
        op(args.setBRef(other.mBuffer[i])
            .setBIsActive(other.valueMask().isOn(i))
            .setResultRef(mBuffer[i]));
        mValueMask.set(i, args.resultIsActive());
    }
}


template<typename T, Index Log2Dim>
template<typename CombineOp, typename OtherNodeT>
inline void
LeafNode<T, Log2Dim>::combine2(const LeafNode& b0, const OtherNodeT& b1, CombineOp& op)
{
    if (!this->allocate()) return;

    CombineArgs<T, typename OtherNodeT::ValueType> args;
    for (Index i = 0; i < SIZE; ++i) {
        mValueMask.set(i, b0.valueMask().isOn(i) || b1.valueMask().isOn(i));
        op(args.setARef(b0.mBuffer[i])
            .setAIsActive(b0.valueMask().isOn(i))
            .setBRef(b1.mBuffer[i])
            .setBIsActive(b1.valueMask().isOn(i))
            .setResultRef(mBuffer[i]));
        mValueMask.set(i, args.resultIsActive());
    }
}


////////////////////////////////////////


template<typename T, Index Log2Dim>
template<typename BBoxOp>
inline void
LeafNode<T, Log2Dim>::visitActiveBBox(BBoxOp& op) const
{
    if (op.template descent<LEVEL>()) {
        for (ValueOnCIter i=this->cbeginValueOn(); i; ++i) {
            op.template operator()<LEVEL>(CoordBBox::createCube(i.getCoord(), 1));
        }
    } else {
        op.template operator()<LEVEL>(this->getNodeBoundingBox());
    }
}


template<typename T, Index Log2Dim>
template<typename VisitorOp>
inline void
LeafNode<T, Log2Dim>::visit(VisitorOp& op)
{
    doVisit<LeafNode, VisitorOp, ChildAllIter>(*this, op);
}


template<typename T, Index Log2Dim>
template<typename VisitorOp>
inline void
LeafNode<T, Log2Dim>::visit(VisitorOp& op) const
{
    doVisit<const LeafNode, VisitorOp, ChildAllCIter>(*this, op);
}


template<typename T, Index Log2Dim>
template<typename NodeT, typename VisitorOp, typename ChildAllIterT>
inline void
LeafNode<T, Log2Dim>::doVisit(NodeT& self, VisitorOp& op)
{
    for (ChildAllIterT iter = self.beginChildAll(); iter; ++iter) {
        op(iter);
    }
}


////////////////////////////////////////


template<typename T, Index Log2Dim>
template<typename OtherLeafNodeType, typename VisitorOp>
inline void
LeafNode<T, Log2Dim>::visit2Node(OtherLeafNodeType& other, VisitorOp& op)
{
    doVisit2Node<LeafNode, OtherLeafNodeType, VisitorOp, ChildAllIter,
        typename OtherLeafNodeType::ChildAllIter>(*this, other, op);
}


template<typename T, Index Log2Dim>
template<typename OtherLeafNodeType, typename VisitorOp>
inline void
LeafNode<T, Log2Dim>::visit2Node(OtherLeafNodeType& other, VisitorOp& op) const
{
    doVisit2Node<const LeafNode, OtherLeafNodeType, VisitorOp, ChildAllCIter,
        typename OtherLeafNodeType::ChildAllCIter>(*this, other, op);
}


template<typename T, Index Log2Dim>
template<
    typename NodeT,
    typename OtherNodeT,
    typename VisitorOp,
    typename ChildAllIterT,
    typename OtherChildAllIterT>
inline void
LeafNode<T, Log2Dim>::doVisit2Node(NodeT& self, OtherNodeT& other, VisitorOp& op)
{
    // Allow the two nodes to have different ValueTypes, but not different dimensions.
    static_assert(OtherNodeT::SIZE == NodeT::SIZE,
        "can't visit nodes of different sizes simultaneously");
    static_assert(OtherNodeT::LEVEL == NodeT::LEVEL,
        "can't visit nodes at different tree levels simultaneously");

    ChildAllIterT iter = self.beginChildAll();
    OtherChildAllIterT otherIter = other.beginChildAll();

    for ( ; iter && otherIter; ++iter, ++otherIter) {
        op(iter, otherIter);
    }
}


////////////////////////////////////////


template<typename T, Index Log2Dim>
template<typename IterT, typename VisitorOp>
inline void
LeafNode<T, Log2Dim>::visit2(IterT& otherIter, VisitorOp& op, bool otherIsLHS)
{
    doVisit2<LeafNode, VisitorOp, ChildAllIter, IterT>(
        *this, otherIter, op, otherIsLHS);
}


template<typename T, Index Log2Dim>
template<typename IterT, typename VisitorOp>
inline void
LeafNode<T, Log2Dim>::visit2(IterT& otherIter, VisitorOp& op, bool otherIsLHS) const
{
    doVisit2<const LeafNode, VisitorOp, ChildAllCIter, IterT>(
        *this, otherIter, op, otherIsLHS);
}


template<typename T, Index Log2Dim>
template<
    typename NodeT,
    typename VisitorOp,
    typename ChildAllIterT,
    typename OtherChildAllIterT>
inline void
LeafNode<T, Log2Dim>::doVisit2(NodeT& self, OtherChildAllIterT& otherIter,
    VisitorOp& op, bool otherIsLHS)
{
    if (!otherIter) return;

    if (otherIsLHS) {
        for (ChildAllIterT iter = self.beginChildAll(); iter; ++iter) {
            op(otherIter, iter);
        }
    } else {
        for (ChildAllIterT iter = self.beginChildAll(); iter; ++iter) {
            op(iter, otherIter);
        }
    }
}


////////////////////////////////////////


template<typename T, Index Log2Dim>
inline std::ostream&
operator<<(std::ostream& os, const typename LeafNode<T, Log2Dim>::Buffer& buf)
{
    for (Index32 i = 0, N = buf.size(); i < N; ++i) os << buf.mData[i] << ", ";
    return os;
}
#endif

} // namespace tree
} // namespace OPENVDB_VERSION_NAME
} // namespace openvdb


////////////////////////////////////////


// Specialization for LeafNodes of type bool
//#include "LeafNodeBool.h"

// Specialization for LeafNodes with mask information only
//#include "LeafNodeMask.h"

#endif // OPENVDB_TREE_LEAFNODE_HAS_BEEN_INCLUDED
