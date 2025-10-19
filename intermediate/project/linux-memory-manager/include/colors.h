/****************************************************************/
/******* Author    : Mahmoud Abdelraouf Mahmoud *****************/
/******* Date      : 8 Apr 2023                 *****************/
/******* Version   : 0.1                        *****************/
/******* File Name : colors.h                   *****************/
/****************************************************************/

/**
 * @file colors.h
 * @brief Header file for ANSI color definitions.
 *
 * This file contains ANSI color definitions used for terminal output coloring.
 */

#ifndef COLORS_H_
#define COLORS_H_

#define ANSI_COLOR_RED "\x1b[31m"     /**< Red ANSI color code. */
#define ANSI_COLOR_GREEN "\x1b[32m"   /**< Green ANSI color code. */
#define ANSI_COLOR_YELLOW "\x1b[33m"  /**< Yellow ANSI color code. */
#define ANSI_COLOR_BLUE "\x1b[34m"    /**< Blue ANSI color code. */
#define ANSI_COLOR_MAGENTA "\x1b[35m" /**< Magenta ANSI color code. */
#define ANSI_COLOR_CYAN "\x1b[36m"    /**< Cyan ANSI color code. */
#define ANSI_COLOR_RESET "\x1b[0m"    /**< ANSI color reset code. */

#endif /**< COLORS_H_ */
