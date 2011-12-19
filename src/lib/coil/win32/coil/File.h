// -*- C++ -*-
/*!
 * @file File_win32.h
 * @brief File functions
 * @date $Date$
 * @author Noriaki Ando <n-ando@aist.go.jp>
 *
 * Copyright (C) 2008
 *     Task-intelligence Research Group,
 *     Intelligent Systems Research Institute,
 *     National Institute of
 *         Advanced Industrial Science and Technology (AIST), Japan
 *     All rights reserved.
 *
 * $Id$
 *
 */

#ifndef COIL_FILE_H
#define COIL_FILE_H

#include <windows.h>
#include <coil/config_coil.h>
#include <coil/stringutil.h>

namespace coil
{
  const unsigned int MaxPathLength(1024);

  /*!
  *  @note like ACE.
  */
  /*!
   * @if jp
   *
   * @brief �t�@�C���p�X���f�B���N�g���������擾����
   *
   * �t�@�C���p�X���f�B���N�g���������擾����B
   *
   * @param path �t�@�C���p�X
   *
   * @return �f�B���N�g������
   *
   * @else
   *
   * @brief Get a directory part than a file pass
   *
   * Get a directory part than a file pass.
   *
   * @param path File path
   *
   * @return Directory name
   *
   * @endif
   */
  inline std::string dirname(char* path)
  {
    char return_dirname[MaxPathLength + 1];

    size_t len = strlen(path);
    if (len > (sizeof(return_dirname) / sizeof(char)))
    {
      len = sizeof(return_dirname) / sizeof(char);
    }
    std::strncpy(return_dirname, path, len);
    return_dirname[len] = '\0';

    const char delimiter('/');
    char *p = std::strrchr(return_dirname, delimiter);

    std::string dir_name;
    if (p)
    {
      if(p != return_dirname)
      {
        if(*(p+1) == '\0')
        {
           *p = '\0';
           dir_name = dirname(return_dirname);
        }
        else
        {
           *p = '\0';
           dir_name = return_dirname;
        }
      }
      else 
      {
        *(p+1) = '\0';
        dir_name = return_dirname;
      }
    }
    else
    {
      dir_name = ".";
    }
    return dir_name;
  }

  /*!
   * @if jp
   *
   * @brief �t�@�C���p�X���t�@�C�����������擾����
   *
   * �t�@�C���p�X���t�@�C�����������擾����B
   *
   * @param path �t�@�C���p�X
   *
   * @return �t�@�C������
   *
   * @else
   *
   * @brief Get a file name part than a file pass
   *
   * Get a directory part than a file pass.
   *
   * @param path File path
   *
   * @return File name
   *
   * @endif
   */
  inline std::string basename(const char* path)
  {
    char p[MaxPathLength + 1];

    size_t len = strlen(path);
    if (len > (sizeof(p) / sizeof(char)))
    {
      len = sizeof(p) / sizeof(char);
    }
    std::strncpy(p, path, len);
    p[len] = '\0';

    const char delimiter('/');
    char *pdelimiter = std::strrchr(p, delimiter);

    std::string base_name(p);
    if (pdelimiter)
    {
      if(pdelimiter != p)
      {
        if(*(pdelimiter+1) == '\0')
        {
          *pdelimiter = '\0';
          base_name = basename(p);
        }
        else
        {
          pdelimiter++;
          base_name = pdelimiter;
        }
      }
      else
      {
        if(*(pdelimiter+1) != '\0')
        {
          pdelimiter++;
          base_name = pdelimiter;
        }
        else
        {
          base_name = pdelimiter;
        }

      }
    }
    return base_name;
  }



  typedef unsigned int ino_t;
  
  /*!
   * @if jp
   *
   * @brief �f�B���N�g���G���g���p�\����
   *
   * @else
   *
   * @brief Structure for directory entry
   *
   * @endif
   */
  struct dirent
  {
    ino_t          d_ino;
    char           d_name[_MAX_PATH];
  };

  /*!
   * @if jp
   *
   * @brief �f�B���N�g���X�g���[���p�\����
   *
   * @else
   *
   * @brief Structure for directory stream
   *
   * @endif
   */
  typedef struct
  {
    HANDLE h;
    WIN32_FIND_DATAA *fd;
    BOOL has_next;
    struct dirent entry;
  } DIR;


  /*!
   * @if jp
   *
   * @brief �f�B���N�g���X�g���[�����I�[�v������
   *
   * �f�B���N�g���X�g���[�����I�[�v������B
   *
   * @param name �t�@�C���p�X
   *
   * @return DIR �\���̃|�C���^
   *
   * @else
   *
   * @brief Open a directory stream
   *
   * Open a directory stream.
   *
   * @param name File path
   *
   * @return DIR Structure pointer
   *
   * @endif
   */
  DIR* opendir(const char *name)
  {
    if (name == 0) { return 0; }
    std::string path(name);
    if (path.empty()) { return 0; }

    // path has at least one or more path characters
    if (*(path.end() - 1) != '\\' && *(path.end() - 1) != '/')
      {
        std::string::size_type pos(path.find("/"));
        if (pos == std::string::npos) { path.push_back('\\'); } // delim = '\'
        else                          { path.push_back('/');  } // delim = '/'
      }
    path.push_back('*'); // now path is "/dir/dir/../*"

    // fd will be held by DIR structure
    HANDLE dhandle;
    WIN32_FIND_DATAA* fd;
    try
      {
        fd = new WIN32_FIND_DATAA();
        dhandle = FindFirstFileA(path.c_str(), fd);
        if (dhandle == INVALID_HANDLE_VALUE) { delete fd; return 0; }

      }
    catch (...)
      {
        FindClose(dhandle);
        return 0;
      }

    DIR* dir;
    try
      {
        dir = new DIR();
        dir->h = dhandle;
        dir->fd = fd;
        dir->has_next = TRUE;
      }
    catch (...)
      {
        delete fd;
        return 0;
      }
    return dir;
  }


  /*!
   * @if jp
   *
   * @brief �f�B���N�g���G���g���|�C���^���擾����
   *
   * �f�B���N�g���G���g���|�C���^���擾����B
   *
   * @param dir DIR �\���̃|�C���^
   *
   * @return DIR �G���g���|�C���^
   *
   * @else
   *
   * @brief Get a directory entry pointer
   *
   * Get a directory entry pointer.
   *
   * @param dir DIR Structure pointer
   *
   * @return DIR entry pointer
   *
   * @endif
   */
  dirent* readdir(DIR *dir)
  {
    if (dir == 0) { return 0; }
    if (dir->fd == 0) { return 0;}
    if (!dir->has_next) { return 0; }

    strcpy_s(dir->entry.d_name, _MAX_PATH, dir->fd->cFileName);
    dir->has_next = FindNextFileA(dir->h, dir->fd);
 
    return &dir->entry;
  }

  /*!
   * @if jp
   *
   * @brief �f�B���N�g���X�g���[�������
   *
   * �f�B���N�g���X�g���[�������B
   *
   * @param dir DIR �\���̃|�C���^
   *
   * @return 0: ����, -1: ���s
   *
   * @else
   *
   * @brief Close a directory stream
   *
   * Close a directory stream.
   *
   * @param dir DIR Structure pointer
   *
   * @return 0: successful, -1: failed
   *
   * @endif
   */
  int closedir(DIR *dir)
  {
    if (dir == 0) { return -1; }
    if (dir->h != 0 && dir->h != INVALID_HANDLE_VALUE)
      {
        FindClose(dir->h);
      }
    if (dir->fd != 0) { delete dir->fd; }
    delete dir;

    return 0;
  }



  /*!
   * @if jp
   *
   * @brief �t�@�C�����X�g���擾����
   *
   * �f�B���N�g���p�X�̒��Ŏw��t�@�C���Ƀ}�b�`���郊�X�g���擾����B
   *
   * @param path �f�B���N�g���p�X
   * @param glob_str �t�@�C����
   *
   * @return �t�@�C�����X�g
   *
   * @else
   *
   * @brief Get file list
   *
   * Get a list matching a file designated than a directory path.
   *
   * @param path Directory path
   * @param glob_str File name
   *
   * @return File list
   *
   * @endif
   */
  inline coil::vstring filelist(const char* path, const char* glob_str = "")
  {
    struct dirent* ent; 
    coil::vstring flist;
    bool has_glob(false);
    std::string pattern;

    if (path == 0) { return flist; }
    if (glob_str[0] != '\0') { has_glob = true; }

    DIR* dir_ptr(coil::opendir(path));
    if (dir_ptr == 0) { return flist; }
    
    while ((ent = coil::readdir(dir_ptr)) != 0)
      {
        bool match(true);
        if (has_glob)
          {
            const char* globc(glob_str);
            std::string fname(ent->d_name);
            for (size_t i(0); i < fname.size() && globc != '\0'; ++i, ++globc)
              {
                if (*globc == '*')
                  {
                    // the last '*' matches every thing
                    if (globc[1] == '\0') { break; }
                    // consecutive * or + are skiped, but fname keeps pointer
                    if (globc[1] == '*' || globc[1] == '+') { --i; continue; }

                    // advance pointer and find normal characters
                    ++globc;
                    size_t pos(fname.find(*globc, i));
                    if (pos == std::string::npos) { match = false; break; }
                    // matched, and advance i to pos
                    i = pos;
                  }
                else if (*globc == '+')
                  {
                    // the last '+' matches last one or more characters
                    if (globc[1] == '\0' && !(i + 1 < fname.size())) { break; }
                    // consecutive * or + are skiped, but fname keeps pointer
                    if (globc[1] == '*' || globc[1] == '+') { --i; continue; }

                    // advance pointer and find normal characters
                    ++globc;
                    size_t pos(fname.find(*globc, i + 1));
                    if (pos == std::string::npos) { match = false; break; }
                    // matched, and advance i to pos
                    i = pos;
                  }
                else
                  {
                    if (fname[i] != *globc) { match = false; }
                  }
                
                // in the last fname character, if glob is not end,
                // or *, fname is not matched.
                if (i + 1 == fname.size() && 
                    globc[1] != '\0' && globc[1] != '*') { match = false; }
              }
          }
        if (match) { flist.push_back(ent->d_name); }
      }
    coil::closedir(dir_ptr);

    return flist;
  }


};

#endif // COIL_FILE_H
