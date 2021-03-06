/*
 * This file is part of NumptyPhysics <http://thp.io/2015/numptyphysics/>
 * Coyright (c) 2009, 2010 Tim Edmonds <numptyphysics@gmail.com>
 * Coyright (c) 2014 Thomas Perl <m@thp.io>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 */

#ifndef NUMPTYPHYSICS_SCENE_H
#define NUMPTYPHYSICS_SCENE_H

#include "Common.h"
#include "Path.h"
#include "Canvas.h"
#include "Script.h"
#include "Interactions.h"
#include "JetStream.h"
#include "SceneEvent.h"

#include <string>
#include <fstream>
#include <vector>
#include <list>
#include <map>


class Stroke;
class b2World;
class Accelerometer;


class Scene : private b2ContactListener
{
public:

  Scene( bool noWorld=false );
  ~Scene();

  bool onSceneEvent(const SceneEvent &ev);

  Stroke* newStroke( const Path& p, int colour, int attributes );
  bool deleteStroke( Stroke *s );
  void extendStroke( Stroke* s, const Vec2& pt );
  void moveStroke( Stroke* s, const Vec2& origin );
  bool activateStroke( Stroke *s );
  std::list<Vec2> getJointCandidates(Stroke *s);

  JetStream *newJetStream(const Vec2 &pos);

  int numStrokes() {
    return m_strokes.size();
  }

  std::vector<Stroke*>& strokes() {
    return m_strokes;
  }

  bool canInteractAt(const Vec2 &pos);
  bool interact(const Vec2 &pos);

  void step();
  bool introCompleted();
  bool isCompleted();
  void draw(Canvas &canvas, bool everything=false);
  Stroke* strokeAtPoint( const Vec2 pt, float32 max );
  void clear();
  bool replay();

  void setGravity( const b2Vec2& g );
  void setGravity( const std::string& s );

  bool load(const std::string &level);
  bool start();
  void protect( int n=-1 );
  bool save( const std::string& file, bool saveLog=false );

  ScriptLog* getLog() { return &m_log; }
  int getTicks() { return m_ticks; }

  void playbackUntil(ScriptLog &log, int ticks);
private:
  bool addJetStream(const char *x, const char *y, const char *width, const char *height, const char *force);
  void resetWorld();
  bool activate( Stroke *s );
  void activateAll();
  void createJoints( Stroke *s );
  std::map<int,Rect> calcColorRects();

  // b2ContactListener callback when a new contact is detected
  virtual void Add(const b2ContactPoint* point) ;


  b2World        *m_world;
  std::vector<Stroke*>  m_strokes;
  std::vector<Stroke*>  m_deletedStrokes;
  std::string     m_title, m_author, m_bg;
  ScriptLog       m_log;
  ScriptRecorder  m_recorder;
  ScriptPlayer    m_player;
  Image          *m_bgImage;
  static Image   *g_bgImage;
  int             m_protect;
  b2Vec2          m_gravity;
  b2Vec2          m_currentGravity;
  bool            m_dynamicGravity;
  Accelerometer  *m_accelerometer;
  int             m_step;
  int             m_ticks;
  std::map<int,Rect> m_color_rects;
  NP::Interactions    m_interactions;
  std::vector<JetStream *> m_jetStreams;

  // Create and move stuff
  Stroke  	   *m_createStroke;
  JetStream        *m_createJetStream;
  Stroke           *m_moveStroke;
  Vec2              m_moveOffset;
  bool              m_paused;

  friend class SceneSVGVisitor;
};

#endif /* NUMPTYPHYSICS_SCENE_H */
