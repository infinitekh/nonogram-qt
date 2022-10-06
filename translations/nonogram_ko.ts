<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1" language="ko_KR" sourcelanguage="en">
<context>
    <name>Dialog</name>
    <message>
        <location filename="../dialog.ui" line="14"/>
        <source>Dialog</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../dialog.ui" line="54"/>
        <source>Width</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../dialog.ui" line="80"/>
        <source>Height</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../dialog.ui" line="106"/>
        <source>Puzzle Number</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>MainWindow</name>
    <message>
        <location filename="../mainwindow.cpp" line="6"/>
        <source>&amp;File</source>
        <translation>파일</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="7"/>
        <location filename="../mainwindow.cpp" line="12"/>
        <source>&amp;Help</source>
        <translation>도움말</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="10"/>
        <source>E&amp;xit</source>
        <translation>나가기</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="14"/>
        <source>&amp;About</source>
        <translation>&amp;About</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="32"/>
        <source>Columns:</source>
        <translation>열</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="33"/>
        <source>Rows:</source>
        <translation>줄</translation>
    </message>
    <message>
        <source>Generate puzzle</source>
        <translation type="vanished">퍼즐 만들기</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="34"/>
        <source>Generate puzzle(Random)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="36"/>
        <source>Generate puzzle(Specified)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="38"/>
        <source>Give up</source>
        <translation>포기하기</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="279"/>
        <source>Well done</source>
        <translation>잘했어요!!!</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="280"/>
        <source>You have solved the puzzle!</source>
        <translation>퍼즐을 푸셨어요.</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="401"/>
        <source>About</source>
        <translation>About</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="402"/>
        <source>&lt;p&gt;&lt;h3&gt;Nonogram-qt 1.1.1&lt;/h3&gt;&lt;/p&gt;&lt;p&gt;Copyright: Daniel Suni, 2012, 2013, 2018&lt;/p&gt;&lt;p&gt;Distributed under the GNU GPL v3&lt;/p&gt;</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="408"/>
        <source>Help</source>
        <translation>도움말</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="410"/>
        <source>&lt;h2&gt;What are nonograms?&lt;/h2&gt;&lt;p&gt;Nonograms are logic puzzles consisting of a rectangular grid divided into cells. These cells can be either&lt;br&gt;colored (solids) or blank (dots). At the start of the game all cells are blank, and the purpose of the game is&lt;br&gt;to figure out which ones should be colored.&lt;/p&gt;&lt;p&gt;Each row and column in the grid is fitted with a clue consisting of a series of numbers. These numbers reveal&lt;br&gt;how many solids there are on the row/column as well as something about their grouping. If e.g. the clue is&lt;br&gt;(3 1 2) we know that from left to right there is first a series of 3 consequtive solids, then X number of blanks,&lt;br&gt;where X &gt;= 1, then a single solid, then another unspecified number of blanks, and finally 2 consequtive solids.&lt;br&gt;If the row was 10 cells long, one possible arrangement would be (-###-#--##), another one would be (###-#-##--).&lt;br&gt;Since there are rules for both rows and columns, only one arrangement is actually correct, though. The puzzle is&lt;br&gt;to find the arrangement that conforms to all the given clues.&lt;/p&gt;&lt;h2&gt;How to play&lt;/h2&gt;&lt;p&gt;In order to start a new game, please select the size of the desired playing field, and click the &amp;quot;Generate puzzle&amp;quot;&lt;br&gt;button. Generating the puzzle can take a few seconds - especially if it&apos;s a big one, so please be patient.&lt;/p&gt;&lt;p&gt;When starting all cells are blank. You can mark a cell as a solid by clicking on it. You can also mark larger areas&lt;br&gt;by dragging the mouse with the button pressed. If you&apos;ve made a mistake, just click the cell again to revert it to a&lt;br&gt;dot. You can also mark known dots by right clicking (and dragging). This will be shown by an &apos;X&apos; appearing in that&lt;br&gt;cell. Notice that you don&apos;t need to explicitly mark the dots in order to solve the puzzle. That functionality only&lt;br&gt;exists for your own convenience.&lt;/p&gt;&lt;p&gt;Every time you make a move the computer will automatically check whether you&apos;ve successfully solved the puzzle&lt;br&gt; or not. Once the puzzle is solved, you will immediately be informed. If the puzzle turns out to be too hard, you can&lt;br&gt;end it, and look at the solution by pressing the &amp;quot;Give up&amp;quot; button. Remaining solids will be displayed in&lt;br&gt;grey, and possible mistakes (i.e. dots marked as solids) will be displayed in red.&lt;/p&gt;</source>
        <translation>&lt;h2&gt;노노그램이란 무엇일까요?&lt;/h2&gt;&lt;p&gt;노노그램은 직사각형 격자로 셀을 나눈 논리 퍼즐입니다. &lt;br/&gt; 이 셀들은 속이 칠해진 색으로나 빈칸으로 표현될 수 있습니다.  먼저 게임이 시작할 때는 모두 빈칸입니다.  게임의 목적은 색이 칠해진 셀을 찾는 것입니다. &lt;/p&gt;&lt;p&gt;Nonograms are logic puzzles consisting of a rectangular grid divided into cells. These cells can be either&lt;br&gt;colored (solids) or blank (dots). At the start of the game all cells are blank, and the purpose of the game is&lt;br&gt;to figure out which ones should be colored.&lt;/p&gt;&lt;p&gt;Each row and column in the grid is fitted with a clue consisting of a series of numbers. These numbers reveal&lt;br&gt;how many solids there are on the row/column as well as something about their grouping. If e.g. the clue is&lt;br&gt;(3 1 2) we know that from left to right there is first a series of 3 consequtive solids, then X number of blanks,&lt;br&gt;where X &gt;= 1, then a single solid, then another unspecified number of blanks, and finally 2 consequtive solids.&lt;br&gt;If the row was 10 cells long, one possible arrangement would be (-###-#--##), another one would be (###-#-##--).&lt;br&gt;Since there are rules for both rows and columns, only one arrangement is actually correct, though. The puzzle is&lt;br&gt;to find the arrangement that conforms to all the given clues.&lt;/p&gt;&lt;h2&gt;How to play&lt;/h2&gt;&lt;p&gt;In order to start a new game, please select the size of the desired playing field, and click the &amp;quot;Generate puzzle&amp;quot;&lt;br&gt;button. Generating the puzzle can take a few seconds - especially if it&apos;s a big one, so please be patient.&lt;/p&gt;&lt;p&gt;When starting all cells are blank. You can mark a cell as a solid by clicking on it. You can also mark larger areas&lt;br&gt;by dragging the mouse with the button pressed. If you&apos;ve made a mistake, just click the cell again to revert it to a&lt;br&gt;dot. You can also mark known dots by right clicking (and dragging). This will be shown by an &apos;X&apos; appearing in that&lt;br&gt;cell. Notice that you don&apos;t need to explicitly mark the dots in order to solve the puzzle. That functionality only&lt;br&gt;exists for your own convenience.&lt;/p&gt;&lt;p&gt;Every time you make a move the computer will automatically check whether you&apos;ve successfully solved the puzzle&lt;br&gt; or not. Once the puzzle is solved, you will immediately be informed. If the puzzle turns out to be too hard, you can&lt;br&gt;end it, and look at the solution by pressing the &amp;quot;Give up&amp;quot; button. Remaining solids will be displayed in&lt;br&gt;grey, and possible mistakes (i.e. dots marked as solids) will be displayed in red.&lt;/p&gt;</translation>
    </message>
</context>
</TS>
