#!/usr/bin/env python3

import os
import argparse
import time

def matches_criteria(filepath, args):
    if args.name and args.name not in os.path.basename(filepath):
        return False

    if args.ext and not filepath.endswith(args.ext):
        return False

    if args.min_size or args.max_size:
        size = os.path.getsize(filepath)
        if args.min_size and size < args.min_size:
            return False
        if args.max_size and size > args.max_size:
            return False

    if args.modified:
        mtime = os.path.getmtime(filepath)
        days_ago = time.time() - (args.modified * 86400)
        if mtime < days_ago:
            return False

    return True

def search_files(root, args):
    for dirpath, _, filenames in os.walk(root):
        for filename in filenames:
            full_path = os.path.join(dirpath, filename)
            try:
                if matches_criteria(full_path, args):
                    print(full_path)
            except Exception as e:
                print(f"Error checking {full_path}: {e}")

def main():
    parser = argparse.ArgumentParser(description="Simple file search tool (like 'find').")
    parser.add_argument("path", help="Starting directory to search")
    parser.add_argument("--name", help="Search for partial filename match")
    parser.add_argument("--ext", help="Search for files with this extension (e.g. .txt)")
    parser.add_argument("--min-size", type=int, help="Minimum file size in bytes")
    parser.add_argument("--max-size", type=int, help="Maximum file size in bytes")
    parser.add_argument("--modified", type=int, help="Only show files modified in the last N days")

    args = parser.parse_args()

    if not os.path.isdir(args.path):
        print("Invalid directory path.")
        return

    search_files(args.path, args)

if __name__ == "__main__":
    main()
