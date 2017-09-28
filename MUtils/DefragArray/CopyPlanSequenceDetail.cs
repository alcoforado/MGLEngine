using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MUtils.DefragArray
{
    public class CopyPlanSequenceDetail<T>
    {
        public CopyPlan Copy;
        public List<CopyPlan> BlockCopyPlan { get; set; }
        public List<CopyPlanSequenceDetail<T>> Blocks { get; set; }
        public List<CopyPlanSequenceDetail<T>> IsBlockedBy { get; private set; }

        public T[] Backup { get; set; }

        public CopyPlanSequenceDetail(CopyPlan copy)
        {
            this.Copy = copy;
            this.IsBlockedBy = new List<CopyPlanSequenceDetail<T>>();
            this.Blocks = new List<CopyPlanSequenceDetail<T>>();
            this.Backup = null;
        }

        internal void ApplyBackup<T>(T[] src)
        {
            System.Diagnostics.Debug.Assert(Backup != null);
            Array.Copy(Backup, 0, src, this.Copy.Dst.offI, this.Copy.Dst.size);
        }

        public void CreateBackup(T[] src)
        {
            Backup = new T[this.Copy.Orig.size];
            Array.Copy(src,Copy.Orig.offI,Backup,0,Copy.Orig.size);
           
        }

        public void RemoveBlocks()
        {
            foreach (var e in Blocks)
            {
                bool found = e.IsBlockedBy.Remove(this);
                if (!found)
                    throw new Exception("Consistency Error found in blocks construction");
            }
        }


    }
}
