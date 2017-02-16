/*
 * minispinlock.h
 *
 *  Created on: 2012-01-27
 *      Author: Francis Giraldeau <francis.giraldeau@gmail.com>
 */

#ifndef MINISPINLOCK_H_
#define MINISPINLOCK_H_

void lock_mini_spin(int *lock);
void unlock_mini_spin(int *lock);

#endif /* MINISPINLOCK_H_ */
