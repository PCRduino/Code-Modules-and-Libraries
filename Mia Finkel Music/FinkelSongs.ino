/* FinkelSongs.ino by Maia Finkel on 5/15/16
   Code to play Mia Finkel's songs.
   Attach the following music modules:
     - "musicNotes.ino"
     - "toneModule_MaiaFinkel.ino"
     - "twinkleTwinkleDbMajor.ino"
     - "Super_Mario_Song.ino"

   Copyright Maia Finkel 2016.  All Rights Reserved.
   No part of these contents may be reproduced, copied, modified or adapted,
   without the prior written consent of the author, unless when used for educational
   and non-profit purposes.
*/

void playAllSongs() {
  while (true) {
    SUPERMARIOBROS();
    twinkleTwinkleDbMajor();
  }
}
