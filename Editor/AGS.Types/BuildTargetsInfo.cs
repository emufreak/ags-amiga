﻿using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Text;

namespace AGS.Types
{
    // FIXME: this class should not be in AGS.Types at all.
    // There should not be any global static collections of interface-implementing
    // objects in AGS.Types. Also - no hardcoded target names.
    // Keep in mind: AGS.Types may be linked to virtually any program, not just Editor.
    // Unfortunately it's coupled in AGS.Types.Settings. Need to find out how to
    // decouple it, use assigned reference, or delegate, or anything.
    public class BuildTargetsInfo
    {
        public const string DATAFILE_TARGET_NAME = "DataFile";
        private static IList<IBuildTarget> _buildTargets;

        static BuildTargetsInfo()
        {
            _buildTargets = new List<IBuildTarget>();
        }

        /// <summary>
        /// Includes an IBuildTarget in the list of potential target build platforms.
        /// </summary>
        public static void RegisterBuildTarget(IBuildTarget target)
        {
            if (target == null) throw new ArgumentNullException("Build targets cannot be null!");
            if (string.IsNullOrEmpty(target.Name)) throw new ArgumentException("Build target names cannot be null or empty!");
            foreach (IBuildTarget bt in _buildTargets)
            {
                if (bt == target) return;   // build target already registered, ignore it
                if (bt.Name == target.Name) // otherwise, if two targets share the same name
                {
                    throw new ArgumentException("Another build target with the same name ('" + target.Name + "') already exists.");
                }
            }
            _buildTargets.Add(target);
        }

        /// <summary>
        /// Returns a read-only list of the IBuildTargets that are currently registered,
        /// regardless of whether they are selected or available for building.
        /// </summary>
        public static IList<IBuildTarget> GetRegisteredBuildTargets(bool onlyNormalTargets)
        {
            if (!onlyNormalTargets)
            {
                return new ReadOnlyCollection<IBuildTarget>(_buildTargets);
            }
            IList<IBuildTarget> result = new List<IBuildTarget>(_buildTargets);
            foreach (IBuildTarget target in _buildTargets)
            {
                if (!target.IsNormalBuildTarget) result.Remove(target);
            }
            return new ReadOnlyCollection<IBuildTarget>(result);
        }

        public static IList<IBuildTarget> GetRegisteredBuildTargets()
        {
            return GetRegisteredBuildTargets(false);
        }

        /// <summary>
        /// Returns a list of the registered build targets which are
        /// currently available for building.
        /// </summary>
        public static IList<IBuildTarget> GetAvailableBuildTargets()
        {
            IList<IBuildTarget> targets = GetRegisteredBuildTargets(true);
            List<IBuildTarget> result = new List<IBuildTarget>(targets);
            foreach (IBuildTarget target in targets)
            {
                if (!target.IsAvailable) result.Remove(target);
            }
            return result;
        }

        /// <summary>
        /// Returns a list of the names of all available build targets.
        /// </summary>
        public static string[] GetAvailableBuildTargetNames()
        {
            IList<IBuildTarget> targets = GetAvailableBuildTargets();
            string[] names = new string[targets.Count];
            for (int i = 0; i < targets.Count; ++i)
            {
                names[i] = targets[i].Name;
            }
            return names;
        }

        /// <summary>
        /// Returns a list of the names of all registered build targets.
        /// </summary>
        public static string[] GetRegisteredBuildTargetNames(bool onlyNormalTargets)
        {
            List<string> names = new List<string>(_buildTargets.Count);
            for (int i = 0; i < _buildTargets.Count; ++i)
            {
                if (onlyNormalTargets ? _buildTargets[i].IsNormalBuildTarget : true)
                {
                    names.Add(_buildTargets[i].Name);
                }
            }
            return names.ToArray();
        }

        public static string[] GetRegisteredBuildTargetNames()
        {
            return GetRegisteredBuildTargetNames(false);
        }

        /// <summary>
        /// Returns a list of the IBuildTargets that are currently available and selected
        /// for building.
        /// </summary>
        public static IList<IBuildTarget> GetSelectedBuildTargets()
        {
            List<IBuildTarget> targets = new List<IBuildTarget>(_buildTargets.Count);
            foreach (IBuildTarget target in _buildTargets)
            {
                if (target.IsTargetedForBuild)
                {
                    targets.Add(target);
                }
            }
            return targets;
        }

        /// <summary>
        /// Locates a registered IBuildTarget by its name, (e.g, "Windows").
        /// </summary>
        public static IBuildTarget FindBuildTargetByName(string name)
        {
            if (string.IsNullOrEmpty(name)) return null;
            foreach (IBuildTarget target in _buildTargets)
            {
                if (target.Name == name)
                {
                    return target;
                }
            }
            return null;
        }
    }
}
