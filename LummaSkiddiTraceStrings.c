/* ////////////////////////////////////////////////////////////////////
// Reverse Engineered from the Lumma Stealer Binary               //
//                                                                 //
// This function is a perfect example of skid-tier coding. It's    //
// supposed to deobfuscate strings by removing the weak-ass        //
// "edx765" marker that these wannabe malware devs slapped on.     //
// Seriously, this level of obfuscation is laughable—no real       //
// malware developer would rely on something this fragile.         //
//                                                                 //
// So, what does this dumpster fire do?                            //
// 1. It scans the input string for instances of "edx765".        //
// 2. Counts how many times it appears (because apparently,        //
//    they couldn't even come up with a better encoding method).   //
// 3. Allocates a new buffer (hope they free it later, but skids   //
//    usually don't) that excludes "edx765" from the original.    //
// 4. Copies over everything except their pathetic obfuscation tag.//
//                                                                 //
// This function is used in the stealer to remove unnecessary     //
// junk markers from strings before processing or displaying them. //
// But come on, even the most basic static analysis will see       //
// through this weak encoding.                                     //
//                                                                 //
// Final thoughts? This isn't even skiddy-level evasion—it's a     //
// desperate attempt by clueless malware devs who think a simple   //
// substring removal equals "encryption." If your stealer is this //
// bad, just quit now.                                             //
///////////////////////////////////////////////////////////////////// */

char* __fastcall TrasStrings(char* src) {
  char *p, *out, *ptr, *match;
  unsigned int len = strlen(src);
  int cnt = 0;

  for (p = strstr(src, "edx765"); p; p = strstr(p + 6, "edx765"))
    ++cnt;

  out = (char *)malloc(len - 6 * cnt + 1);
  if (!out) return NULL;

  ptr = out;
  match = strstr(src, "edx765");

  while (match) {
    int diff = match - src;
    strncpy(ptr, src, diff);
    ptr += diff;
    src = match + 6;
    match = strstr(src, "edx765");
  }

  strcpy(ptr, src);
  return out;
}
