using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MUtils.DefragArray
{
    public struct FragmentRegion
    {
        public int offI;
        public int size;

        public bool ContinuouslyFollows(FragmentRegion dst)
        {
            return (this.offI == dst.offI + dst.size);
        }

        public bool Overlaps(FragmentRegion dst)
        {
            if (dst.offI > this.offI)
                return dst.offI - this.offI < this.size;
            else
                return this.offI - dst.offI < dst.size;
        }


        public bool IsAfter(FragmentRegion frag)
        {
            return frag.offI + frag.size < this.offI;
        }

        public bool Intersects(FragmentRegion frag)
        {
            return !(frag.offI + frag.size <= this.offI || frag.offI  >= this.offI + this.size);
        }
    }

    public class CopyPlan
    {
        public FragmentRegion Dst;
        public FragmentRegion Orig;

        public bool TryRightMerge(CopyPlan copyPlan)
        {
            if (copyPlan.Orig.ContinuouslyFollows(this.Orig) &&
                copyPlan.Dst.ContinuouslyFollows(this.Dst))
            {
                this.Orig.size += copyPlan.Orig.size;
                this.Dst.size  += copyPlan.Dst.size;
                return true;
            }
            return false;
        }

        public bool IsRightOf(CopyPlan cp)
        {
            return true;
        }
    }

}
